# 🚀 Krypton - A Version Control System

*A lightweight, fast, and modular version control system inspired by Git.*

## 🌟 Features
- 🛠️ **Custom CLI** with PD Curses UI
- 🔗 **File Tracking** (`krypton add`, `krypton commit`)
- 🌿 **Branching & Merging** (`krypton branch`, `krypton merge`)
- 📝 **Commit History Logging** (`krypton log`)
- 🔍 **File Differences** (`krypton diff`)
- 🏎️ **Optimized for Speed & Efficiency**

## 📌 Installation
```bash
# Clone the Krypton repository
git clone https://github.com/Samsung-Studio/Krypton.git
cd Krypton

# Build the project (C++ Example)
make
```

## 🚀 Quick Start
```bash
# Initialize a Krypton repository
krypton init

# Add files to the staging area
krypton add file.txt

# Commit changes
krypton commit -m "Initial commit"

# View commit history
krypton log
```

## 📂 Project Structure
```
📂 Krypton/
   │── 📂 build/                         # Compiled binaries & build artifacts
   │      ├── 📂 bin/                    # Stores executable files
   │      │      ├── krypton.exe         # Main Krypton executable
   │      ├── 📂 obj/                    # Stores object files (.o) generated from compilation
   │      │      ├── 📂 command/
   │      │      │      ├── parse.o      # Object file for parsing CLI commands
   │      │      │      ├── ui.o         # Object file for handling UI operations
   │      │      ├── 📂 core/
   │      │      │      ├── vcs.o        # Object file for version control system logic
   │      │      │      ├── index.o      # Object file for index management
   │      │      │      ├── commit.o     # Object file for commit management
   │      │      │      ├── branch.o     # Object file for branch handling
   │      │      │      ├── diff.o       # Object file for showing code differences
   │      │      │      ├── checkout.o   # Object file for checkout functionality
   │      │      │      ├── stash.o      # Object file for stashing changes
   │      │      │      ├── remote.o     # Object file for handling remote repositories
   │      │      ├── 📂 utils/
   │      │      │      ├── file_io.o    # Object file for file I/O operations
   │      │      │      ├── logger.o     # Object file for logging events
   │      │      │      ├── utils.o      # Object file for general utility functions
   │      │      │      ├── hashing.o    # Object file for hashing functions
   │      │      │      ├── config.o     # Object file for configuration handling
   │      │      ├── krypton.o           # Object file for the main program entry point
   │
   │── 📂 assets/                        # Stores external assets like icons, themes, and fonts
   │      ├── 📂 icons/                  # Stores icons used in the UI and executables
   │      │      ├── krypton.ico         # Main executable icon
   │      ├── 📂 themes/                 # Stores UI theme configuration files
   │      ├── 📂 fonts/                  # Stores custom fonts for UI
   │      ├── 📂 banners/                # ASCII banners for CLI interface
   │      ├── 📂 sounds/                 # Stores notification sounds
   │      ├── 📂 docs/                   # Stores documentation-related assets
   |      |__ 📂 resources/              # Stores resources needed for compilation
   |      |      |__ icon.rc             # Resource file for defining application icons
   |      |      |__ krypton.res         # Compiled resource file for icons
   │
   │── 📂 include/                       # Header files (.h) containing function declarations
   │      ├── 📂 command/                # Headers for CLI command processing
   │      │      ├── parse.h             # Function declarations for parsing CLI commands
   │      │      ├── ui.h                # Function declarations for UI operations
   │      ├── 📂 core/                   # Headers for core version control system logic
   │      │      ├── vcs.h               # Function declarations for version control system
   │      │      ├── index.h             # Function declarations for index management
   │      │      ├── commit.h            # Function declarations for commit handling
   │      │      ├── branch.h            # Function declarations for branch operations
   │      │      ├── diff.h              # Function declarations for diff generation
   │      │      ├── checkout.h          # Function declarations for checkout functionality
   │      │      ├── stash.h             # Function declarations for stash management
   │      │      ├── remote.h            # Function declarations for remote repository handling
   │      ├── 📂 utils/                  # Headers for utility functions
   │      │      ├── file_io.h           # Function declarations for file I/O operations
   │      │      ├── logger.h            # Function declarations for logging system
   │      │      ├── utils.h             # Function declarations for general utilities
   │      │      ├── hashing.h           # Function declarations for hashing algorithms
   │      │      ├── config.h            # Function declarations for configuration management
   │
   │── 📂 src/                           # Source files (.cpp) containing function definitions
   │      ├── 📂 command/                # Handles command execution logic
   │      │      ├── parse.cpp           # Implements CLI command parsing
   │      │      ├── ui.cpp              # Implements UI logic using PDCurses
   │      ├── 📂 core/                   # Implements core version control system logic
   │      │      ├── vcs.cpp             # Implements main VCS functionality
   │      │      ├── index.cpp           # Implements index handling
   │      │      ├── commit.cpp          # Implements commit operations
   │      │      ├── branch.cpp          # Implements branch management
   │      │      ├── diff.cpp            # Implements diff comparison
   │      │      ├── checkout.cpp        # Implements checkout feature
   │      │      ├── stash.cpp           # Implements stash operations
   │      │      ├── remote.cpp          # Implements remote repository handling
   │      ├── 📂 utils/                  # Implements utility functions
   │      │      ├── file_io.cpp         # Implements file I/O operations
   │      │      ├── logger.cpp          # Implements logging functionality
   │      │      ├── utils.cpp           # Implements general utility functions
   │      │      ├── hashing.cpp         # Implements hashing algorithms
   │      │      ├── config.cpp          # Implements configuration parsing
   │
   │── krypton.cpp                       # Main entry point of the program (contains main())
   │
   │── 📂 tests/                         # Unit tests for the application
   │      ├── test_vcs.cpp               # Tests for version control system logic
   │      ├── test_hashing.cpp           # Tests for hashing functions
   │      ├── test_commit.cpp            # Tests for commit operations
   │
   │── 📂 .krypton/                      # Stores internal Krypton metadata (like .git folder)
   │      ├── objects/                   # Stores versioned objects using hashed IDs
   │      ├── refs/                      # Stores branch and reference data
   │      ├── HEAD                       # Points to the current branch
   │
   │── .gitignore                        # Specifies files to ignore in Git repository
   │── Makefile                          # Automates the build process using Make
   │── README.md                         # Project documentation (setup, usage, etc.)
```

## 👥 Contributors
- **Krishna Verma** - <krishnaverma.0227@gmail.com>
- **Ayush Chamoli** - <Chamoli2004@gmail.com>
- **Sneha Mishra**  - <snehami1412@gmail.com>
- **Sanghmitra Kandpal** - <sanghmitrakandpal@gmail.com>

## 🎯 Roadmap
- [ ] Implement `krypton push/pull`
- [ ] Improve merge conflict resolution
- [ ] Enhance CLI with more UI elements

## 🛠️ Contributing
We welcome contributions! Read our [CONTRIBUTING.md](CONTRIBUTING.md) for details.

## 📜 License
This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

---
🔥 **Built with passion by the Krypton Team!** 🔥