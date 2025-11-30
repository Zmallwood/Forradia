# A Simple Linux Dashboard made with Python.
# Edit quicklaunchapps.py to add more app shortcuts.
# Edit asciilogo.py to add more ascii logos.

# Import Modules
import customtkinter as ctk
import os
import subprocess
from PIL import Image


# Set up the dashboard window
class Dashboard(ctk.CTk):
    def __init__(self):
        super().__init__()

        # Get the directory of the dashboard
        self.script_dir = os.path.dirname(os.path.abspath(__file__))

        self.title("Forradia Dashboard")

        # Window Size
        window_width = 1020
        window_height = 875
        self.geometry(f"{window_width}x{window_height}")

        # Allow window resizing
        self.resizable(True, True)

        # Set minimum window size
        self.minsize(800, 500)

        # Default Theme
        ctk.set_appearance_mode("dark")
        ctk.set_default_color_theme("blue")

        self.grid_columnconfigure(1, weight=1)
        self.grid_rowconfigure(0, weight=1)

        # Main area frame
        self.main_frame = ctk.CTkScrollableFrame(self, fg_color="#002255")
        self.main_frame.grid(row=0, column=1, sticky="nsew")
        self.main_frame.grid_columnconfigure(0, weight=1)
        self.main_frame.grid_rowconfigure(1, weight=1)
        self.main_frame.pack(fill="both", expand=True)

        self.create_area_project()
        self.create_area_a()
        self.create_area_b()
        self.create_area_c()
        self.create_area_d()
        self.create_area_e()
        self.create_area_f()
        self.create_area_g()
        self.create_area_h()
        self.create_area_i()

    def create_area_project(self):
        center_frame = ctk.CTkFrame(self.main_frame, fg_color="transparent")
        center_frame.grid(row=0, column=0, sticky="nsew")
        center_frame.grid_rowconfigure(0, weight=1)
        center_frame.grid_columnconfigure(0, weight=1)

        quick_launch_frame = ctk.CTkFrame(
            center_frame,
            corner_radius=10,
            border_width=2,
            border_color="gray30",
            fg_color="#004477",
        )
        quick_launch_frame.grid(row=0, column=0, padx=20, pady=20, sticky="nsew")
        quick_launch_frame.grid_rowconfigure(0, weight=1)
        quick_launch_frame.grid_columnconfigure(0, weight=1)

        apps_label = ctk.CTkLabel(
            quick_launch_frame, text="Project", font=("Noto Sans", 20, "bold")
        )
        apps_label.grid(row=0, column=0, pady=(10, 10), sticky="n")

        app_frame = ctk.CTkFrame(quick_launch_frame, fg_color="transparent")
        app_frame.grid(row=1, column=0, pady=(10, 10), sticky="n")

        create_app_button(
            app_frame,
            "Repository",
            "cursor",
            "/home/andreas/code/git/Forradia/Forradia.code-workspace",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
            "#AAAA00",
        )

        create_app_button(
            app_frame,
            "CMake",
            "cursor",
            "/home/andreas/code/git/Forradia/CMake.code-workspace",
            "icons/DefaultButton.png",
            1,
            0,
            self.script_dir,
            "#AAAA00",
        )

    def create_area_a(self):
        center_frame = ctk.CTkFrame(self.main_frame, fg_color="transparent")
        center_frame.grid(row=1, column=0, sticky="nsew")
        center_frame.grid_rowconfigure(0, weight=1)
        center_frame.grid_columnconfigure(0, weight=1)

        quick_launch_frame = ctk.CTkFrame(
            center_frame,
            corner_radius=10,
            border_width=2,
            border_color="gray30",
            fg_color="#004477",
        )
        quick_launch_frame.grid(row=0, column=0, padx=20, pady=20, sticky="nsew")
        quick_launch_frame.grid_rowconfigure(0, weight=1)
        quick_launch_frame.grid_columnconfigure(0, weight=1)

        apps_label = ctk.CTkLabel(
            quick_launch_frame,
            text="A. Dependencies for many",
            font=("Noto Sans", 20, "bold"),
        )
        apps_label.grid(row=0, column=0, pady=(10, 10), sticky="n")

        app_frame = ctk.CTkFrame(quick_launch_frame, fg_color="transparent")
        app_frame.grid(row=1, column=0, pady=(10, 10), sticky="n")

        create_app_button(
            app_frame,
            "A1. Common Lang",
            "cursor",
            "/home/andreas/code/git/Forradia/CommonLang.code-workspace",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
            "#007700",
        )

        create_app_button(
            app_frame,
            "A2. Common General",
            "cursor",
            "/home/andreas/code/git/Forradia/CommonGeneral.code-workspace",
            "icons/DefaultButton.png",
            1,
            0,
            self.script_dir,
            "#007700",
        )

        create_app_button(
            app_frame,
            "A3. Common Matter",
            "cursor",
            "/home/andreas/code/git/Forradia/CommonMatter.code-workspace",
            "icons/DefaultButton.png",
            2,
            0,
            self.script_dir,
            "#007700",
        )

    def create_area_b(self):
        center_frame = ctk.CTkFrame(self.main_frame, fg_color="transparent")
        center_frame.grid(row=2, column=0, sticky="nsew")
        center_frame.grid_rowconfigure(0, weight=1)
        center_frame.grid_columnconfigure(0, weight=1)

        quick_launch_frame = ctk.CTkFrame(
            center_frame, corner_radius=10, border_width=2, border_color="gray30",
            fg_color="#004477"
        )
        quick_launch_frame.grid(row=0, column=0, padx=20, pady=20, sticky="nsew")
        quick_launch_frame.grid_rowconfigure(0, weight=1)
        quick_launch_frame.grid_columnconfigure(0, weight=1)

        apps_label = ctk.CTkLabel(
            quick_launch_frame,
            text="B. Dependencies for many",
            font=("Noto Sans", 20, "bold"),
        )
        apps_label.grid(row=0, column=0, pady=(10, 10), sticky="n")

        app_frame = ctk.CTkFrame(quick_launch_frame, fg_color="transparent")
        app_frame.grid(row=1, column=0, pady=(10, 10), sticky="n")

        create_app_button(
            app_frame,
            "B1. Common Utilities",
            "cursor",
            "/home/andreas/code/git/Forradia/CommonUtilities.code-workspace",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
            "#007700",
        )

        create_app_button(
            app_frame,
            "B2. Common Core Utilities",
            "cursor",
            "/home/andreas/code/git/Forradia/CommonCoreUtilities.code-workspace",
            "icons/DefaultButton.png",
            1,
            0,
            self.script_dir,
            "#007700",
        )

    def create_area_c(self):
        center_frame = ctk.CTkFrame(self.main_frame, fg_color="transparent")
        center_frame.grid(row=3, column=0, sticky="nsew")
        center_frame.grid_rowconfigure(0, weight=1)
        center_frame.grid_columnconfigure(0, weight=1)

        quick_launch_frame = ctk.CTkFrame(
            center_frame, corner_radius=10, border_width=2, border_color="gray30",
            fg_color="#004477"
        )
        quick_launch_frame.grid(row=0, column=0, padx=20, pady=20, sticky="nsew")
        quick_launch_frame.grid_rowconfigure(0, weight=1)
        quick_launch_frame.grid_columnconfigure(0, weight=1)

        apps_label = ctk.CTkLabel(
            quick_launch_frame,
            text="C. Dependencies for >= D1",
            font=("Noto Sans", 20, "bold"),
        )
        apps_label.grid(row=0, column=0, pady=(10, 10), sticky="n")

        app_frame = ctk.CTkFrame(quick_launch_frame, fg_color="transparent")
        app_frame.grid(row=1, column=0, pady=(10, 10), sticky="n")

        create_app_button(
            app_frame,
            "C1. Core Graphics Devices",
            "cursor",
            "/home/andreas/code/git/Forradia/CoreGraphicsDevices.code-workspace",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "C2. Core Assets",
            "cursor",
            "/home/andreas/code/git/Forradia/CoreAssets.code-workspace",
            "icons/DefaultButton.png",
            1,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "C3. Core Input",
            "cursor",
            "/home/andreas/code/git/Forradia/CoreInput.code-workspace",
            "icons/DefaultButton.png",
            2,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "C4. Core Rendering Common",
            "cursor",
            "/home/andreas/code/git/Forradia/CoreRenderingCommon.code-workspace",
            "icons/DefaultButton.png",
            3,
            0,
            self.script_dir,
            "#990000",
        )

    def create_area_d(self):
        center_frame = ctk.CTkFrame(self.main_frame, fg_color="transparent")
        center_frame.grid(row=4, column=0, sticky="nsew")
        center_frame.grid_rowconfigure(0, weight=1)
        center_frame.grid_columnconfigure(0, weight=1)

        quick_launch_frame = ctk.CTkFrame(
            center_frame, corner_radius=10, border_width=2, border_color="gray30",
            fg_color="#004477"
        )
        quick_launch_frame.grid(row=0, column=0, padx=20, pady=20, sticky="nsew")
        quick_launch_frame.grid_rowconfigure(0, weight=1)
        quick_launch_frame.grid_columnconfigure(0, weight=1)

        apps_label = ctk.CTkLabel(
            quick_launch_frame,
            text="D. Dependencies for >= E",
            font=("Noto Sans", 20, "bold"),
        )
        apps_label.grid(row=0, column=0, pady=(10, 10), sticky="n")

        app_frame = ctk.CTkFrame(quick_launch_frame, fg_color="transparent")
        app_frame.grid(row=1, column=0, pady=(10, 10), sticky="n")

        create_app_button(
            app_frame,
            "D1. Core Rendering Colors 2D",
            "cursor",
            "/home/andreas/code/git/Forradia/CoreRenderingColors2D.code-workspace",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "D2. Core Rendering Images 2D",
            "cursor",
            "/home/andreas/code/git/Forradia/CoreRenderingImages2D.code-workspace",
            "icons/DefaultButton.png",
            1,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "D3. Core Rendering Text",
            "cursor",
            "/home/andreas/code/git/Forradia/CoreRenderingText.code-workspace",
            "icons/DefaultButton.png",
            2,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "D4. Core Rendering Ground",
            "cursor",
            "/home/andreas/code/git/Forradia/CoreRenderingGround.code-workspace",
            "icons/DefaultButton.png",
            3,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "D5. Core Rendering Models",
            "cursor",
            "/home/andreas/code/git/Forradia/CoreRenderingModels.code-workspace",
            "icons/DefaultButton.png",
            4,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "D5. Core Rendering Sky",
            "cursor",
            "/home/andreas/code/git/Forradia/CoreRenderingSky.code-workspace",
            "icons/DefaultButton.png",
            5,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "D6. Theme 0 World Structure",
            "cursor",
            "/home/andreas/code/git/Forradia/Theme0WorldStructure.code-workspace",
            "icons/DefaultButton.png",
            0,
            1,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "D7. Theme 0 Properties",
            "cursor",
            "/home/andreas/code/git/Forradia/Theme0Properties.code-workspace",
            "icons/DefaultButton.png",
            1,
            1,
            self.script_dir,
        )

    def create_area_e(self):
        center_frame = ctk.CTkFrame(self.main_frame, fg_color="transparent")
        center_frame.grid(row=5, column=0, sticky="nsew")
        center_frame.grid_rowconfigure(0, weight=1)
        center_frame.grid_columnconfigure(0, weight=1)

        quick_launch_frame = ctk.CTkFrame(
            center_frame, corner_radius=10, border_width=2, border_color="gray30",
            fg_color="#004477"
        )
        quick_launch_frame.grid(row=0, column=0, padx=20, pady=20, sticky="nsew")
        quick_launch_frame.grid_rowconfigure(0, weight=1)
        quick_launch_frame.grid_columnconfigure(0, weight=1)

        apps_label = ctk.CTkLabel(
            quick_launch_frame,
            text="E. Dependencies for >= F",
            font=("Noto Sans", 20, "bold"),
        )
        apps_label.grid(row=0, column=0, pady=(10, 10), sticky="n")

        app_frame = ctk.CTkFrame(quick_launch_frame, fg_color="transparent")
        app_frame.grid(row=1, column=0, pady=(10, 10), sticky="n")

        create_app_button(
            app_frame,
            "E1. Core GUI",
            "cursor",
            "/home/andreas/code/git/Forradia/CoreGUI.code-workspace",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "E2. Theme 0 World Generation Common",
            "cursor",
            "/home/andreas/code/git/Forradia/Theme0WorldGenerationCommon.code-workspace",
            "icons/DefaultButton.png",
            0,
            1,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "E2. Theme 0 World Generation Ground",
            "cursor",
            "/home/andreas/code/git/Forradia/Theme0WorldGenerationGround.code-workspace",
            "icons/DefaultButton.png",
            1,
            1,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "E2. Theme 0 World Generation Water",
            "cursor",
            "/home/andreas/code/git/Forradia/Theme0WorldGenerationWater.code-workspace",
            "icons/DefaultButton.png",
            2,
            1,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "E2. Theme 0 World Generation Objects",
            "cursor",
            "/home/andreas/code/git/Forradia/Theme0WorldGenerationObjects.code-workspace",
            "icons/DefaultButton.png",
            3,
            1,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "E2. Theme 0 World Generation Entities",
            "cursor",
            "/home/andreas/code/git/Forradia/Theme0WorldGenerationEntities.code-workspace",
            "icons/DefaultButton.png",
            4,
            1,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "E2. Theme 0 World Generation Main",
            "cursor",
            "/home/andreas/code/git/Forradia/Theme0WorldGenerationMain.code-workspace",
            "icons/DefaultButton.png",
            0,
            2,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "E3. Theme 0 Essentials",
            "cursor",
            "/home/andreas/code/git/Forradia/Theme0Essentials.code-workspace",
            "icons/DefaultButton.png",
            0,
            3,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "E4. Core Minor Components",
            "cursor",
            "/home/andreas/code/git/Forradia/CoreMinorComponents.code-workspace",
            "icons/DefaultButton.png",
            1,
            3,
            self.script_dir,
            "#990000",
        )

    def create_area_f(self):
        center_frame = ctk.CTkFrame(self.main_frame, fg_color="transparent")
        center_frame.grid(row=6, column=0, sticky="nsew")
        center_frame.grid_rowconfigure(0, weight=1)
        center_frame.grid_columnconfigure(0, weight=1)

        quick_launch_frame = ctk.CTkFrame(
            center_frame, corner_radius=10, border_width=2, border_color="gray30",
            fg_color="#004477"
        )
        quick_launch_frame.grid(row=0, column=0, padx=20, pady=20, sticky="nsew")
        quick_launch_frame.grid_rowconfigure(0, weight=1)
        quick_launch_frame.grid_columnconfigure(0, weight=1)

        apps_label = ctk.CTkLabel(
            quick_launch_frame,
            text="F. Dependencies for >= G",
            font=("Noto Sans", 20, "bold"),
        )
        apps_label.grid(row=0, column=0, pady=(10, 10), sticky="n")

        app_frame = ctk.CTkFrame(quick_launch_frame, fg_color="transparent")
        app_frame.grid(row=1, column=0, pady=(10, 10), sticky="n")

        create_app_button(
            app_frame,
            "F1. Core Scenes",
            "cursor",
            "/home/andreas/code/git/Forradia/CoreScenes.code-workspace",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
            "#990000",
        )

    def create_area_g(self):
        center_frame = ctk.CTkFrame(self.main_frame, fg_color="transparent")
        center_frame.grid(row=7, column=0, sticky="nsew")
        center_frame.grid_rowconfigure(0, weight=1)
        center_frame.grid_columnconfigure(0, weight=1)

        quick_launch_frame = ctk.CTkFrame(
            center_frame, corner_radius=10, border_width=2, border_color="gray30",
            fg_color="#004477"
        )
        quick_launch_frame.grid(row=0, column=0, padx=20, pady=20, sticky="nsew")
        quick_launch_frame.grid_rowconfigure(0, weight=1)
        quick_launch_frame.grid_columnconfigure(0, weight=1)

        apps_label = ctk.CTkLabel(
            quick_launch_frame,
            text="G. Dependencies for >= H",
            font=("Noto Sans", 20, "bold"),
        )
        apps_label.grid(row=0, column=0, pady=(10, 10), sticky="n")

        app_frame = ctk.CTkFrame(quick_launch_frame, fg_color="transparent")
        app_frame.grid(row=1, column=0, pady=(10, 10), sticky="n")

        create_app_button(
            app_frame,
            "G1. Core Engine",
            "cursor",
            "/home/andreas/code/git/Forradia/CoreEngine.code-workspace",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
            "#990000",
        )

    def create_area_h(self):
        center_frame = ctk.CTkFrame(self.main_frame, fg_color="transparent")
        center_frame.grid(row=8, column=0, sticky="nsew")
        center_frame.grid_rowconfigure(0, weight=1)
        center_frame.grid_columnconfigure(0, weight=1)

        quick_launch_frame = ctk.CTkFrame(
            center_frame, corner_radius=10, border_width=2, border_color="gray30",
            fg_color="#004477"
        )
        quick_launch_frame.grid(row=0, column=0, padx=20, pady=20, sticky="nsew")
        quick_launch_frame.grid_rowconfigure(0, weight=1)
        quick_launch_frame.grid_columnconfigure(0, weight=1)

        apps_label = ctk.CTkLabel(
            quick_launch_frame,
            text="H. Dependencies for >= I",
            font=("Noto Sans", 20, "bold"),
        )
        apps_label.grid(row=0, column=0, pady=(10, 10), sticky="n")

        app_frame = ctk.CTkFrame(quick_launch_frame, fg_color="transparent")
        app_frame.grid(row=1, column=0, pady=(10, 10), sticky="n")

        create_app_button(
            app_frame,
            "H1. Theme 0 Core",
            "cursor",
            "/home/andreas/code/git/Forradia/Theme0Core.code-workspace",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "H2. Theme 0 Custom GUI",
            "cursor",
            "/home/andreas/code/git/Forradia/Theme0CustomGUI.code-workspace",
            "icons/DefaultButton.png",
            1,
            0,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "H3. Theme 0",
            "cursor",
            "/home/andreas/code/git/Forradia/Theme0.code-workspace",
            "icons/DefaultButton.png",
            2,
            0,
            self.script_dir,
        )

    def create_area_i(self):
        center_frame = ctk.CTkFrame(self.main_frame, fg_color="transparent")
        center_frame.grid(row=9, column=0, sticky="nsew")
        center_frame.grid_rowconfigure(0, weight=1)
        center_frame.grid_columnconfigure(0, weight=1)

        quick_launch_frame = ctk.CTkFrame(
            center_frame, corner_radius=10, border_width=2, border_color="gray30",
            fg_color="#004477"
        )
        quick_launch_frame.grid(row=0, column=0, padx=20, pady=20, sticky="nsew")
        quick_launch_frame.grid_rowconfigure(0, weight=1)
        quick_launch_frame.grid_columnconfigure(0, weight=1)

        apps_label = ctk.CTkLabel(
            quick_launch_frame, text="I. Runtime", font=("Noto Sans", 20, "bold")
        )
        apps_label.grid(row=0, column=0, pady=(10, 10), sticky="n")

        app_frame = ctk.CTkFrame(quick_launch_frame, fg_color="transparent")
        app_frame.grid(row=1, column=0, pady=(10, 10), sticky="n")

        create_app_button(
            app_frame,
            "I1. Theme 0 Scripts",
            "cursor",
            "/home/andreas/code/git/Forradia/Theme0Scripts.code-workspace",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
        )


def create_app_button(
    parent, app_name, command, path, icon_path, column, row, script_dir, color="#0055DD"
):
    def open_app():
        subprocess.run([command, path, "-r"])

    # Use absolute path for the icon
    full_icon_path = os.path.join(script_dir, icon_path)

    # Load and resize the icon
    icon = ctk.CTkImage(Image.open(full_icon_path), size=(60, 60))

    button = ctk.CTkButton(
        parent,
        text=app_name,
        image=icon,
        compound="top",
        command=open_app,
        width=100,
        height=100,
        corner_radius=10,
        fg_color=color,
        hover_color="#AA00AA",
    )
    button.grid(row=row, column=column, padx=10, pady=10)


if __name__ == "__main__":
    app = Dashboard()
    app.mainloop()
