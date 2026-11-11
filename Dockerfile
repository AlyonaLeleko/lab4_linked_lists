FROM ubuntu:22.04 AS builder
RUN apt-get update && apt-get install -y cmake g++ && rm -rf /var/lib/apt/lists/*
WORKDIR /app
COPY . .
RUN cmake -S . -B build -DBUILD_TESTING=OFF && cmake --build build
FROM ubuntu:22.04
WORKDIR /app
COPY --from=builder /app/build/lab4 .
CMD ["./lab4"]
