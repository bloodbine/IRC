# Use Alpine Linux as base image
FROM alpine:latest

# Install irssi IRC client
RUN apk --no-cache add irssi

# Create a directory for irssi configuration
RUN mkdir -p /root/.irssi

WORKDIR /irssi
