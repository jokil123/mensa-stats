FROM node:latest AS builder
WORKDIR /mensa-stats
COPY package.json package-lock.json ./
RUN npm ci

COPY . .
RUN npm run build


FROM node:latest AS runner
WORKDIR /mensa-stats
COPY package.json package-lock.json ./
RUN npm ci --omit dev

COPY --from=builder /mensa-stats/build build

EXPOSE 3000
CMD ["node", "build"]