#!/usr/bin/env python3
"""
Script to find unused #include directives in C++ files.

This script analyzes C++ source files and identifies potentially unused includes
by attempting to compile each file with individual includes removed.
"""

import json
import re
import shlex
import subprocess
import tempfile
import os
import sys
from pathlib import Path
from typing import List, Tuple, Optional
from collections import defaultdict

def extract_includes(content: str) -> List[Tuple[int, str, str]]:
    """
    Extract all #include directives from file content.
    Returns list of (line_number, include_type, include_path) tuples.
    include_type is either 'system' (<>) or 'local' ("")
    """
    includes = []
    lines = content.split('\n')
    
    for i, line in enumerate(lines, 1):
        # Match #include directives
        match = re.match(r'^\s*#include\s+([<"])([^>"]+)([>"])', line)
        if match:
            quote_type = match.group(1)
            include_path = match.group(2)
            include_type = 'system' if quote_type == '<' else 'local'
            includes.append((i, include_type, include_path))
    
    return includes

def remove_include_from_content(content: str, line_num: int) -> str:
    """Remove the include at the specified line number."""
    lines = content.split('\n')
    if 1 <= line_num <= len(lines):
        lines.pop(line_num - 1)
    return '\n'.join(lines)

def get_compile_command_for_file(compile_commands: dict, file_path: str) -> Optional[dict]:
    """Find the compile command for a given file in compile_commands.json."""
    # Normalize paths
    file_path = os.path.abspath(file_path)
    
    for entry in compile_commands:
        entry_file = os.path.abspath(entry['file'])
        if entry_file == file_path:
            return entry
    
    return None

def test_compile_without_include(file_path: str, compile_entry: dict, 
                                  include_line: int, include_path: str) -> bool:
    """
    Test if the file compiles without a specific include.
    Returns True if compilation succeeds (include might be unused).
    """
    # Read original file
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        original_content = f.read()
    
    # Remove the include
    modified_content = remove_include_from_content(original_content, include_line)
    
    # Create temporary file in the same directory as original
    file_dir = os.path.dirname(file_path)
    file_name = os.path.basename(file_path)
    tmp_file_path = os.path.join(file_dir, f'.tmp_{file_name}')
    
    try:
        # Write modified content
        with open(tmp_file_path, 'w', encoding='utf-8') as f:
            f.write(modified_content)
        
        # Extract compile command
        directory = compile_entry['directory']
        command = compile_entry['command']
        
        # Replace the original file path with temp file path in command
        # Handle both absolute and relative paths
        abs_file_path = os.path.abspath(file_path)
        abs_tmp_path = os.path.abspath(tmp_file_path)
        command = command.replace(abs_file_path, abs_tmp_path)
        command = command.replace(file_path, tmp_file_path)
        
        # Parse command into list
        try:
            cmd_parts = shlex.split(command)
        except:
            # Fallback: simple split
            cmd_parts = command.split()
        
        # Modify command to only do syntax checking (don't link)
        # Find compiler
        compiler_idx = -1
        for i, part in enumerate(cmd_parts):
            if 'c++' in part or 'g++' in part or 'clang++' in part:
                compiler_idx = i
                break
        
        if compiler_idx == -1:
            return False
        
        # Build new command: compiler + -fsyntax-only + flags (skip -o and output file)
        new_cmd = [cmd_parts[compiler_idx], '-fsyntax-only']
        
        # Add include directories and other flags, but skip output-related flags
        skip_next = False
        for i, part in enumerate(cmd_parts):
            if i == compiler_idx:
                continue
            if skip_next:
                skip_next = False
                continue
            if part == '-o' or part.startswith('-o'):
                skip_next = True
                continue
            # Skip output file paths (usually .o files)
            if part.endswith('.o') and i > 0 and cmd_parts[i-1] != '-o':
                continue
            # Keep include directories and other flags
            if part.startswith('-I') or part.startswith('-D') or part.startswith('-std=') or \
               part.startswith('-W') or part.startswith('-x') or part == '-include' or \
               part.startswith('-f') or part.startswith('-m') or part.startswith('-pthread'):
                new_cmd.append(part)
                # If -include, also add the next argument
                if part == '-include' and i + 1 < len(cmd_parts):
                    new_cmd.append(cmd_parts[i + 1])
        
        # Add the source file
        new_cmd.append(abs_tmp_path)
        
        # Run compilation
        result = subprocess.run(
            new_cmd,
            cwd=directory,
            capture_output=True,
            text=True,
            timeout=30
        )
        
        return result.returncode == 0
    except Exception as e:
        # If compilation fails for any reason, assume include is needed
        return False
    finally:
        # Clean up temp file
        try:
            if os.path.exists(tmp_file_path):
                os.unlink(tmp_file_path)
        except:
            pass

def analyze_file(file_path: str, compile_commands: dict, verbose: bool = False) -> List[Tuple[int, str, str]]:
    """
    Analyze a single file for unused includes.
    Returns list of (line_number, include_path, include_type) tuples for potentially unused includes.
    """
    # Get compile command for this file
    compile_entry = get_compile_command_for_file(compile_commands, file_path)
    if not compile_entry:
        if verbose:
            print(f"  Warning: No compile command found for {file_path}")
        return []
    
    # Read file
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
    except Exception as e:
        if verbose:
            print(f"  Error reading {file_path}: {e}")
        return []
    
    # Extract includes
    includes = extract_includes(content)
    if not includes:
        return []
    
    unused = []
    
    # Test each include (skip the first one if it's the corresponding header)
    for line_num, include_type, include_path in includes:
        # Skip if this is likely the corresponding header file
        if include_type == 'local':
            file_base = Path(file_path).stem
            include_base = Path(include_path).stem
            if file_base == include_base:
                continue
        
        if verbose:
            quote = '<' if include_type == 'system' else '"'
            end_quote = '>' if include_type == 'system' else '"'
            print(f"    Testing line {line_num}: #include {quote}{include_path}{end_quote}")
        
        # Test compilation without this include
        if test_compile_without_include(file_path, compile_entry, line_num, include_path):
            unused.append((line_num, include_path, include_type))
            if verbose:
                print(f"      -> Potentially unused!")
    
    return unused

def find_workspace_root() -> Path:
    """Find the workspace root by looking for the desktop/build directory."""
    # Start from the script's location
    script_path = Path(__file__).resolve()
    
    # If script is in desktop/Scripts, go up to workspace root
    if 'desktop' in script_path.parts and 'Scripts' in script_path.parts:
        # Find the index of 'desktop' and go up from there
        parts = script_path.parts
        desktop_idx = parts.index('desktop')
        workspace_root = Path(*parts[:desktop_idx])
    else:
        # Try to find workspace root by looking for desktop/build directory
        current = script_path.parent
        while current != current.parent:
            build_dir = current / 'desktop' / 'build'
            if build_dir.exists():
                workspace_root = current
                break
            current = current.parent
        else:
            # Fallback: assume we're in the workspace root
            workspace_root = script_path.parent
            while workspace_root.name != 'Forradia' and workspace_root != workspace_root.parent:
                workspace_root = workspace_root.parent
    
    return workspace_root

def main():
    """Main function to analyze all C++ files in the project."""
    import argparse
    
    parser = argparse.ArgumentParser(description='Find unused #include directives in C++ files')
    parser.add_argument('--file', type=str, help='Analyze a specific file only')
    parser.add_argument('--limit', type=int, help='Limit number of files to analyze')
    parser.add_argument('--verbose', action='store_true', help='Verbose output')
    args = parser.parse_args()
    
    # Find workspace root dynamically
    workspace_root = find_workspace_root()
    compile_commands_path = workspace_root / 'desktop' / 'build' / 'compile_commands.json'
    
    if not compile_commands_path.exists():
        print(f"Error: compile_commands.json not found at {compile_commands_path}")
        print("Please build the project first to generate compile_commands.json")
        sys.exit(1)
    
    # Load compile commands
    print(f"Loading compile commands from {compile_commands_path}...")
    with open(compile_commands_path, 'r') as f:
        compile_commands = json.load(f)
    
    # Find .cpp files
    if args.file:
        # Analyze specific file
        file_path = Path(args.file)
        if file_path.is_absolute():
            cpp_files = [file_path]
        else:
            # Try relative to workspace root first
            cpp_files = [workspace_root / args.file]
            # If not found, try relative to current directory
            if not cpp_files[0].exists():
                cpp_files = [Path(args.file).resolve()]
        if not cpp_files[0].exists():
            print(f"Error: File not found: {args.file}")
            print(f"  Tried: {workspace_root / args.file}")
            print(f"  Tried: {Path(args.file).resolve()}")
            sys.exit(1)
    else:
        # Find all .cpp files
        code_dir = workspace_root / 'desktop' / 'code' / 'client'
        cpp_files = list(code_dir.rglob('*.cpp'))
        if args.limit:
            cpp_files = cpp_files[:args.limit]
    
    print(f"Found {len(cpp_files)} C++ source files")
    print("Analyzing files for unused includes...\n")
    
    results = defaultdict(list)
    total_unused = 0
    
    for cpp_file in sorted(cpp_files):
        relative_path = cpp_file.relative_to(workspace_root)
        print(f"Analyzing {relative_path}...")
        
        unused = analyze_file(str(cpp_file), compile_commands, verbose=args.verbose)
        
        if unused:
            results[str(cpp_file)] = unused
            total_unused += len(unused)
            print(f"  Found {len(unused)} potentially unused include(s):")
            for line_num, include_path, include_type in unused:
                quote = '<' if include_type == 'system' else '"'
                end_quote = '>' if include_type == 'system' else '"'
                print(f"    Line {line_num}: #include {quote}{include_path}{end_quote}")
        else:
            print(f"  No unused includes found")
        print()
    
    # Summary
    print("=" * 80)
    print("SUMMARY")
    print("=" * 80)
    print(f"Total files analyzed: {len(cpp_files)}")
    print(f"Files with unused includes: {len(results)}")
    print(f"Total potentially unused includes: {total_unused}")
    print()
    
    if results:
        print("Files with potentially unused includes:")
        print()
        for file_path, unused_list in sorted(results.items()):
            relative_path = Path(file_path).relative_to(workspace_root)
            print(f"{relative_path}:")
            for line_num, include_path, include_type in unused_list:
                quote = '<' if include_type == 'system' else '"'
                end_quote = '>' if include_type == 'system' else '"'
                print(f"  Line {line_num}: #include {quote}{include_path}{end_quote}")
            print()

if __name__ == '__main__':
    main()

