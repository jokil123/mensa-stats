FROM node:latest as builder
WORKDIR /mensa-stats
COPY . .

RUN npm ci
RUN npm run build


FROM node:latest as runner
WORKDIR /mensa-stats
COPY --from=builder /mensa-stats/build build
COPY package.json package-lock.json ./

RUN npm ci --omit dev

EXPOSE 5173
CMD node build
# ENTRYPOINT ["tail", "-f", "/dev/null"]