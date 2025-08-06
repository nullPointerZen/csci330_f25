# C++ Course Docker Environment

This directory contains the Docker-based development environment for the C++ course.

## Quick Start

### 1. Prerequisites
- Install Docker Desktop from [docker.com](https://docker.com)
- Ensure Docker is running (look for Docker icon in system tray/menu bar)

### 2. Start the Environment

```bash
# Navigate to this directory
cd csci330_f25

# Start the C++ development container
docker-compose up -d cpp-dev

# Enter the container
docker-compose exec cpp-dev bash
```

### 3. Your First Program

Once inside the container:

```bash
# Navigate to first assignment
cd assignment-templates/HW_01

# Build the project
mkdir -p build && cd build
cmake ..
make

# Run the program
./hello_world

# Run tests
make test
```

## Directory Structure

```
csci330_f25/
├── docker-compose.yml       # Container orchestration
├── Dockerfile              # Container definition
├── .devcontainer/          # VS Code integration
├── assignment-templates/   # Assignment starting code
│   └── HW_01/             # First assignment
│       ├── CMakeLists.txt
│       ├── src/           # Source code
│       └── tests/         # Unit tests
└── upcoming-assignments/   # Future assignments
```

## VS Code Integration

For the best experience, use VS Code with Docker:

1. Install VS Code from [code.visualstudio.com](https://code.visualstudio.com)
2. Install the "Remote - Containers" extension
3. Open this folder in VS Code
4. Click "Reopen in Container" when prompted

## Common Commands

| Command | Purpose |
|---------|---------|
| `docker-compose up -d cpp-dev` | Start container |
| `docker-compose exec cpp-dev bash` | Enter container |
| `docker-compose down` | Stop container |
| `docker-compose restart cpp-dev` | Restart container |
| `docker-compose logs cpp-dev` | View container logs |

## Tools Available

The container includes:
- **g++** - GNU C++ compiler
- **cmake** - Build system
- **gdb** - Debugger
- **valgrind** - Memory checker
- **clang-format** - Code formatter
- **catch2** - Testing framework
- **git** - Version control
- **nano/vim** - Text editors

## Troubleshooting

### Container won't start
```bash
docker-compose down
docker-compose build --no-cache
docker-compose up -d cpp-dev
```

### Permission issues
- Make sure Docker Desktop is running
- On Linux, ensure your user is in the docker group

### Can't find tools
- All tools are pre-installed in the container
- Make sure you're working inside the container, not on your host

## Assignment Workflow

1. Start with template in `assignment-templates/`
2. Copy to your working directory
3. Edit source files in `src/`
4. Build with CMake
5. Test your code
6. Submit via GitHub

## Course Development

This course was developed through an innovative **human-AI collaborative process** that transformed aging course materials into the streamlined learning experience you see today. **AI is a tool, nothing more** - it enhanced systematic implementation while human expertise guided all pedagogical decisions.

📖 **Full Development Story**: See [`../README.md`](../README.md) for the complete methodology and [`../instructor/AI_ASSISTED_DEVELOPMENT.md`](../instructor/AI_ASSISTED_DEVELOPMENT.md) for detailed documentation.

## Support

- Check the main course documentation in the parent directory
- Review `docker_troubleshooting.md` for common issues
- Ask in class or office hours for help

---

**Note**: This environment provides everything needed for the course. No local compiler installation required!