FROM ubuntu:22.04

# Prevent interactive prompts during installation
ENV DEBIAN_FRONTEND=noninteractive

# Install essential C++ development tools
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    git \
    vim \
    nano \
    valgrind \
    clang-format \
    clang-tidy \
    catch2 \
    pkg-config \
    wget \
    curl \
    man \
    less \
    && rm -rf /var/lib/apt/lists/*

# Set up working directory
WORKDIR /workspace

# Set default shell and environment
ENV TERM=xterm-256color
SHELL ["/bin/bash", "-c"]

# Create a non-root user for development
RUN useradd -m -s /bin/bash student && \
    echo "student ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

# Switch to student user
USER student
WORKDIR /home/student/workspace

# Configure bash for better experience
RUN echo 'export PS1="\[\033[01;32m\]student@cpp-dev\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]$ "' >> ~/.bashrc && \
    echo 'alias ll="ls -alF"' >> ~/.bashrc && \
    echo 'alias la="ls -A"' >> ~/.bashrc && \
    echo 'alias l="ls -CF"' >> ~/.bashrc && \
    echo 'alias cls="clear"' >> ~/.bashrc && \
    echo 'echo "Welcome to C++ Course Development Environment!"' >> ~/.bashrc && \
    echo 'echo "Type '\''ls'\'' to see available files, '\''cd modules/module-01_ch1/assignment-template'\'' to start"' >> ~/.bashrc

# Default command
CMD ["/bin/bash"]