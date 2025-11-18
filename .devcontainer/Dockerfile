FROM mcr.microsoft.com/vscode/devcontainers/cpp:ubuntu-22.04

# Install additional development tools
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    cmake \
    gdb \
    build-essential \
    git \
    jq \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set up non-root user
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Ensure the user exists (it should already in this base image)
RUN if ! id -u ${USERNAME} > /dev/null 2>&1; then \
    groupadd --gid $USER_GID $USERNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME \
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME; \
    fi

USER ${USERNAME}