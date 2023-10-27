# Use the official gcc image as a base
FROM gcc:13.2.0

# Set environment variables to non-interactive (this prevents some prompts)
ENV DEBIAN_FRONTEND=non-interactive

# Install basic tools, CMake, build utilities, and openssh-server
RUN apt-get update && \
    apt-get install -y \
    gdb \
    make \
    cmake \
    openssh-server \
    rsync \
    && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Set up SSH server configurations
RUN mkdir /var/run/sshd && \
    echo 'root:root' | chpasswd && \
    sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# SSH login fix to prevent: "Could not load host key"
RUN sed 's@session\s*required\s*pam_loginuid.so@session optional pam_loginuid.so@g' -i /etc/pam.d/sshd

# Expose the SSH port
EXPOSE 22

# Set the default command to run the SSH server in the foreground
CMD ["/usr/sbin/sshd", "-D"]
