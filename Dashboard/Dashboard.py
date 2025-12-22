# A Simple Linux Dashboard made with Python.
# Edit quicklaunchapps.py to add more app shortcuts.
# Edit asciilogo.py to add more ascii logos.

# Import Modules
import customtkinter as ctk
import os
import subprocess
from PIL import Image

opening_app = "neovide"

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
        self.main_frame = ctk.CTkScrollableFrame(self, fg_color="#223344")
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
            fg_color="#334455",
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
            opening_app,
            "/home/andreas/code/git/Forradia",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
            "#AAAA00",
        )

        create_app_button(
            app_frame,
            "CMake",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code",
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
            fg_color="#334455",
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
            "A2. Common General",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CommonGeneral",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
            "#007700",
        )

        create_app_button(
            app_frame,
            "A3. Common Matter",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CommonMatter",
            "icons/DefaultButton.png",
            1,
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
            fg_color="#334455"
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
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CommonUtilities",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
            "#007700",
        )

        create_app_button(
            app_frame,
            "B2. Common Core Utilities",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CommonCoreUtilities",
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
            fg_color="#334455"
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
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CoreGraphicsDevices",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "C2. Core Assets",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CoreAssets",
            "icons/DefaultButton.png",
            1,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "C4. Core Rendering Common",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CoreRenderingCommon",
            "icons/DefaultButton.png",
            2,
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
            fg_color="#334455"
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
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CoreRenderingColors2D",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "D2. Core Rendering Images 2D",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CoreRenderingImages2D",
            "icons/DefaultButton.png",
            1,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "D3. Core Rendering Text",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CoreRenderingText",
            "icons/DefaultButton.png",
            2,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "D4. Core Rendering Ground",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CoreRenderingGround",
            "icons/DefaultButton.png",
            3,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "D5. Core Rendering Models",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CoreRenderingModels",
            "icons/DefaultButton.png",
            4,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "D5. Core Rendering Sky",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CoreRenderingSky",
            "icons/DefaultButton.png",
            5,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "D6. Theme 0 World Structure",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/Theme0WorldStructure",
            "icons/DefaultButton.png",
            0,
            1,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "D7. Theme 0 Properties",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/Theme0Properties",
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
            fg_color="#334455"
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
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CoreGUI",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
            "#990000",
        )

        create_app_button(
            app_frame,
            "E2. Theme 0 World Generation Common",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/Theme0WorldGenerationCommon",
            "icons/DefaultButton.png",
            0,
            1,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "E2. Theme 0 World Generation Ground",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/Theme0WorldGenerationGround",
            "icons/DefaultButton.png",
            1,
            1,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "E2. Theme 0 World Generation Water",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/Theme0WorldGenerationWater",
            "icons/DefaultButton.png",
            2,
            1,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "E2. Theme 0 World Generation Objects",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/Theme0WorldGenerationObjects",
            "icons/DefaultButton.png",
            3,
            1,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "E2. Theme 0 World Generation Entities",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/Theme0WorldGenerationEntities",
            "icons/DefaultButton.png",
            4,
            1,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "E2. Theme 0 World Generation Main",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/Theme0WorldGenerationMain",
            "icons/DefaultButton.png",
            0,
            2,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "E3. Theme 0 Essentials",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/Theme0Essentials",
            "icons/DefaultButton.png",
            0,
            3,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "E4. Core Minor Components",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CoreMinorComponents",
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
            fg_color="#334455"
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
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CoreScenes",
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
            fg_color="#334455"
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
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/CoreEngine",
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
            fg_color="#334455"
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
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/Theme0Core",
            "icons/DefaultButton.png",
            0,
            0,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "H2. Theme 0 Custom GUI",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/Theme0CustomGUI",
            "icons/DefaultButton.png",
            1,
            0,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "H3. Theme 0 Scenes",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/Theme0Scenes",
            "icons/DefaultButton.png",
            2,
            0,
            self.script_dir,
        )

        create_app_button(
            app_frame,
            "H4. Theme 0",
            opening_app,
            "/home/andreas/code/git/Forradia/Desktop/code/client/Theme0",
            "icons/DefaultButton.png",
            3,
            0,
            self.script_dir,
        )


def create_app_button(
    parent, app_name, command, path, icon_path, column, row, script_dir, color="#0055DD"
):
    def open_app():
        #subprocess.run([command, path, "-r"])
        subprocess.run("neovide", cwd=path)

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
