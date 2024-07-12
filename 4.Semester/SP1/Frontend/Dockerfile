#stage 1 build the application
FROM node:16 as node

WORKDIR /app

COPY . .

RUN npm install

RUN npm run build --prod

#stage 2 build the nginx server
FROM nginx:alpine

COPY --from=node /app/dist/frontend_application /usr/share/nginx/html