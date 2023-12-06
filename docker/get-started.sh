# Container

# Create Dockerfile
# syntax=docker/dockerfile:1

FROM node:18-alpine
WORKDIR /app
COPY . .
RUN yarn install --production
CMD ["node", "src/index.js"]
EXPOSE 3000

# Repeat and do any necessary changes to codes 

# Build and rebuild Docker image after each change
docker build -t getting-started .

# Before starting a new container from the new image, 
# stop and remove any existing one
docker ps
docker stop <the-container-id>
docker rm <the-container-id> 

# Run Docker image as container
docker run -dp 127.0.0.1:3000:3000 getting-started

# Check application
xdg-open http://localhost:3000/


# REPOSITORY

# Sign up and create repository. Visibility = Public

# Login as Docker.io user
docker login -u YOUR-USER-NAME

# Tag image under Docker.io user with a new name
docker tag getting-started YOUR-USER-NAME/getting-started

# Push to upload Docker image
docker push YOUR-USER-NAME/getting-started

# Pull and run uploaded public Docker image
docker run -dp 0.0.0.0:3000:3000 YOUR-USER-NAME/getting-started

# GITHUB REPOSITORY

# Login as GitHub user
echo $PAT | docker login ghcr.io --username phanatic --password-stdin

# Tag image under GitHub user with a new name
docker tag getting-started ghcr.io/YOUR-USER-NAME/getting-started:1.0.0

# Push to upload Docker image
docker push ghcr.io/YOUR-USER-NAME/getting-started:1.0.0

# Pull to download Docker image
docker pull ghcr.io/YOUR-USER-NAME/getting-started
docker pull ghcr.io/YOUR-USER-NAME/getting-started:1.0.0
docker pull ghcr.io/YOUR-USER-NAME/getting-started:latest


# VOLUME

# Create volume
docker volume create todo-db

# Mount and run
docker run -dp 127.0.0.1:3000:3000 --mount type=volume,src=todo-db,target=/etc/todos getting-started

# View info
docker volume inspect todo-db

# BIND MOUNT
docker run -it --mount type=bind,src="$(pwd)",target=/src ubuntu bash

# Create and delete files between container and host
# Press CTRL-D to stop interactive session

# Mount storage and install dependencies
docker run -dp 127.0.0.1:3000:3000 \
    -w /app --mount type=bind,src="$(pwd)",target=/app \
    node:18-alpine \
    sh -c "yarn install && yarn run dev"

# Check container logs and console
docker logs -f <container-id>

# Press CTRL-C to stop watching logs

# Rebuild Docker image when done developing/testing
docker build -t getting-started .

# NETWORKING

# Create a network
docker network create todo-app

# Run MySQL on network 'todo-app' 
# Volume 'todo-mysql-data' is created automatically if it does not exist.
# Network-alias
docker run -d \
    --network todo-app --network-alias mysql \
    -v todo-mysql-data:/var/lib/mysql \
    -e MYSQL_ROOT_PASSWORD=secret \
    -e MYSQL_DATABASE=todos \
    mysql:8.0

# Check MySQL is running
docker ps
docker exec -it <mysql-container-id> mysql -u root -p

# Connect to MySQL
docker run -it --network todo-app nicolaka/netshoot

# Query DNS set by '--network-alias mysql'
dig mysql 

# Run the todo app
docker run -dp 127.0.0.1:3000:3000 \
  -w /app -v "$(pwd):/app" \
  --network todo-app \
  -e MYSQL_HOST=mysql \
  -e MYSQL_USER=root \
  -e MYSQL_PASSWORD=secret \
  -e MYSQL_DB=todos \
  node:18-alpine \
  sh -c "yarn install && yarn run dev"

# Check that data is being written to DB
docker exec -it <mysql-container-id> mysql -p todos

mysql> select * from todo_items;

# MULTI-CONTAINER

# Prepare compose.yaml 

# Start
docker compose up -d

# Check logs
docker compose logs -f
docker compose logs -f app

# Stop
docker compose down           # Keep volumes by default
docker compose down --volumes # Remove volumes when stopping








