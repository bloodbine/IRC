# Use Alpine Linux as base image
FROM alpine:latest

# Set the working directory
WORKDIR /irc

# Install required packages
RUN apk update && \
    apk add --no-cache g++ make valgrind tree

# Command to run when the container starts
CMD ["sh"]

