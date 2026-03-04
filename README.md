# MFAM WebUI
This is a proof-of-concept web application for plotting data from a Geometrics' Micro Fabricated Atomic Mangentometer 
(MFAM) in realtime.

## Backend HTTP Server
A simple client/server that communicates with the MFAM via a TCP socket and provides HTTP endpoints for retrieving data.

### Development
Development was done using [CLion](https://www.jetbrains.com/clion/). Most of these steps can be done in any IDE.
1. Install [Qt](https://www.qt.io/development/download-qt-installer-oss) if you haven't already done so.
2. Open the project in CLion.
2. Go to Settings -> build, Execution, Deployment -> CMake
3. Set CMake options to include `-DCMAKE_PREFIX_PATH="C:\Qt\6.10.2\mingw_64"`.
   1. Adjust `C:\Qt\6.10.2\mingw_64` to the path of your Qt installation.
4.


## Frontend Web Application
A simple web application that communicates with the backend HTTP server.

### Development
1. Install Node.js and npm.
2. Install Angular CLI globally using `npm install -g @angular/cli`.
3. Navigate to the frontend directory and run `npm install` to install dependencies.
4. Run `ng serve` to start the development server.
5. Open a web browser and navigate to `http://localhost:4200` to view the application.