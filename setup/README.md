# Development Environment Setup - CSCI 330

## 🚀 Quick Start Guide

### Setup Order (Follow These Steps)
1. **[📋 Development Setup Guide](DEVELOPMENT_SETUP.md)** - Complete installation instructions
2. **[📖 Git Workflow Guide](GIT_WORKFLOW.md)** - Learn the submission process
3. **[✅ Test Your Setup](test_integration.sh)** - Verify everything works

### Additional Resources
- **[🛠️ Docker Troubleshooting](docker_troubleshooting.md)** - Common issues and solutions
- **[📝 Git Commands Reference](../reference/git-commands.md)** - Quick Git reference

## What's In This Directory?

| File | Purpose |
|------|---------|
| `DEVELOPMENT_SETUP.md` | Complete setup instructions for Docker, VS Code, and Git |
| `GIT_WORKFLOW.md` | Professional Git workflow for assignments |
| `docker-compose.yml` | Docker container configuration |
| `Dockerfile` | Container definition with C++ tools |
| `test_integration.sh` | Script to verify your setup |
| `docker_troubleshooting.md` | Solutions for common Docker issues |

## Quick Commands

```bash
# From the course root directory (csci330_f25/)
# Start development environment
docker-compose up -d

# Enter container  
docker exec -it csci330_f25-cpp-dev bash

# Test your setup (from setup/ directory)
cd setup && ./test_integration.sh

# Stop container
docker-compose down
```

## Need Help?
1. Check the troubleshooting guide for your issue
2. Visit office hours for setup assistance
3. Post in the course discussion forum

---

**Ready to begin?** → Start with **[DEVELOPMENT_SETUP.md](DEVELOPMENT_SETUP.md)**