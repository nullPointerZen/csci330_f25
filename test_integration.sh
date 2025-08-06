#!/bin/bash

# Integration test script for C++ course environment
# This script verifies that Git, Docker, VS Code, and C++ tools work together

echo "========================================="
echo "C++ Course Environment Integration Test"
echo "========================================="
echo ""

# Color codes for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Test counter
TESTS_PASSED=0
TESTS_FAILED=0

# Function to check command availability
check_command() {
    if command -v $1 &> /dev/null; then
        echo -e "${GREEN}✓${NC} $1 is installed"
        ((TESTS_PASSED++))
    else
        echo -e "${RED}✗${NC} $1 is not installed"
        ((TESTS_FAILED++))
    fi
}

# Function to check file existence
check_file() {
    if [ -f "$1" ]; then
        echo -e "${GREEN}✓${NC} Found: $1"
        ((TESTS_PASSED++))
    else
        echo -e "${RED}✗${NC} Missing: $1"
        ((TESTS_FAILED++))
    fi
}

# Function to check directory existence
check_dir() {
    if [ -d "$1" ]; then
        echo -e "${GREEN}✓${NC} Found directory: $1"
        ((TESTS_PASSED++))
    else
        echo -e "${RED}✗${NC} Missing directory: $1"
        ((TESTS_FAILED++))
    fi
}

echo "1. Checking host system tools..."
echo "---------------------------------"
check_command git
check_command docker
check_command code

echo ""
echo "2. Checking Git repository..."
echo "------------------------------"
if [ -d ".git" ]; then
    echo -e "${GREEN}✓${NC} Git repository initialized"
    ((TESTS_PASSED++))
    
    # Check for important files in git
    if git ls-files --error-unmatch README.md &> /dev/null; then
        echo -e "${GREEN}✓${NC} README.md is tracked by Git"
        ((TESTS_PASSED++))
    else
        echo -e "${YELLOW}⚠${NC} README.md not tracked by Git"
    fi
else
    echo -e "${RED}✗${NC} Not a Git repository"
    ((TESTS_FAILED++))
fi

echo ""
echo "3. Checking course structure..."
echo "--------------------------------"
check_file "README.md"
check_file ".gitignore"
check_dir "instructor"
check_dir "csci330_f25"
check_dir "chapter_01_solutions"
check_file "chapter_01_complete.md"
check_file "chapter_01_development_setup.md"

echo ""
echo "4. Checking Docker configuration..."
echo "------------------------------------"
check_file "csci330_f25/Dockerfile"
check_file "csci330_f25/docker-compose.yml"
check_dir "csci330_f25/.devcontainer"
check_file "csci330_f25/.devcontainer/devcontainer.json"

echo ""
echo "5. Checking assignment templates..."
echo "------------------------------------"
check_dir "csci330_f25/assignment-templates"
check_dir "csci330_f25/assignment-templates/HW_01"
check_file "csci330_f25/assignment-templates/HW_01/CMakeLists.txt"
check_file "csci330_f25/assignment-templates/HW_01/src/main.cpp"

echo ""
echo "6. Checking Docker service..."
echo "-----------------------------"
if docker info &> /dev/null; then
    echo -e "${GREEN}✓${NC} Docker daemon is running"
    ((TESTS_PASSED++))
    
    # Check if image can be built
    echo "  Testing Docker build (this may take a moment)..."
    if cd csci330_f25 && docker-compose build --quiet cpp-dev &> /dev/null; then
        echo -e "${GREEN}✓${NC} Docker image builds successfully"
        ((TESTS_PASSED++))
    else
        echo -e "${RED}✗${NC} Docker image build failed"
        ((TESTS_FAILED++))
    fi
    cd ..
else
    echo -e "${RED}✗${NC} Docker daemon is not running"
    echo -e "${YELLOW}  → Start Docker Desktop and run this test again${NC}"
    ((TESTS_FAILED++))
fi

echo ""
echo "7. Checking VS Code extensions..."
echo "----------------------------------"
if command -v code &> /dev/null; then
    if code --list-extensions 2>/dev/null | grep -q "ms-vscode.cpptools"; then
        echo -e "${GREEN}✓${NC} C/C++ extension installed"
        ((TESTS_PASSED++))
    else
        echo -e "${YELLOW}⚠${NC} C/C++ extension not installed"
        echo "  → Install with: code --install-extension ms-vscode.cpptools"
    fi
    
    if code --list-extensions 2>/dev/null | grep -q "ms-vscode-remote.remote-containers"; then
        echo -e "${GREEN}✓${NC} Remote-Containers extension installed"
        ((TESTS_PASSED++))
    else
        echo -e "${YELLOW}⚠${NC} Remote-Containers extension not installed"
        echo "  → Install with: code --install-extension ms-vscode-remote.remote-containers"
    fi
fi

echo ""
echo "========================================="
echo "Integration Test Results"
echo "========================================="
echo -e "Tests passed: ${GREEN}$TESTS_PASSED${NC}"
echo -e "Tests failed: ${RED}$TESTS_FAILED${NC}"

if [ $TESTS_FAILED -eq 0 ]; then
    echo -e "\n${GREEN}✓ All integration tests passed!${NC}"
    echo "Your C++ course environment is properly configured."
    exit 0
else
    echo -e "\n${YELLOW}⚠ Some tests failed.${NC}"
    echo "Please address the issues above before proceeding."
    exit 1
fi