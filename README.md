Tired of waiting in the queue at the RWTH Mensa?

# [Mensa-Stats](https://mensa-stats.joshualung.com) tells you how full the mensa is

Mensa-Measures give you an idea of how full the mensa is going to be by measuring the bluetooth devices present using an esp wroom 32 board.

The data collected every five minutes, uploaded to a mongodb database using sveltekit and then displayed using a svelte frontent.

If you have any issues, suggestions or improvements feel free to create a PR or issue.

# Contributing

## Api (and Frontend)

-   `cd api`
-   `npm i` install dependencies
-   `npm run dev` run development server (the enviroment variable DB_URL needs to be set to your mongodb connection url)
-   `npm run build` build project

## Collector

-   install the [platform.io](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) vscode extension
-   open `collector` as a platform.io project or `cd collector`
-   build / upload / monitor using the respective platform.io commands (you will need an esp32 wroom board)
    before building, add an .env file with the following keys:
    ```toml
    DEVICE=<device_id> # id as set in the devices collection
    TOKEN=<device_token> # token as set in the devices collection
    API_URL=<api_url> # the domain the backend is hosted at (for example: https://mensa-stats-backend.com)
    ```

## Database

-   setup mongoDB database
-   create collections

    -   occupancy (time series)

        ```json
        {
            "timestamp": timestamp,
            "metadata": {
                "device": string
            },
            "occupancy": number,
            "_id": ObjectId
        }
        ```

    -   devices (stores tokens for the collectors):
        ```json
        {
            "_id": ObjectId,
            "device": string,
            "token": string
        }
        ```

-   get connection string / url (for example `mongodb://user:12345678@dbdomain.com:36000/my-db`)
