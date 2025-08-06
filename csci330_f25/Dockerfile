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
    && rm -rf /var/lib/apt/lists/*

# Set up working directory
WORKDIR /workspace

# Set default shell and environment
ENV TERM=xterm-256color
SHELL ["/bin/bash", "-c"]

# Create a non-root user for development
RUN useradd -m -s /bin/bash student && \
    echo "student ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

USER student
WORKDIR /home/student/workspace

# Default command
CMD ["/bin/bash"]