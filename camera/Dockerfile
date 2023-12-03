 FROM ubuntu:20.04
 ENV DEBIAN_FRONTEND=noninteractive
 RUN apt-get update && apt-get install -y \
    libopencv-dev \
    && rm -rf /var/lib/apt/lists/*
 WORKDIR /app
 COPY VideoClient /app/VideoClient
 RUN chmod +x /app/VideoClient
 CMD ["/app/VideoClient"]
