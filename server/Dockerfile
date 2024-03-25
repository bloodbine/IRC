# Use Alpine Linux as base image
FROM alpine

# Install necessary packages (g++, make, and Valgrind)
RUN apk --no-cache add g++ make valgrind

# Set the working directory
WORKDIR /server

# Copy your source code and makefile into the container
COPY server.cpp /server
