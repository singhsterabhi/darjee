const electron = require('electron');
const app = electron.app; // Module to control application life.
const BrowserWindow = electron.BrowserWindow; // Module to create native browser window.
const path = require('path');
const {ipcMain} = require('electron');

require('electron-reload')(__dirname);

// Keep a global reference of the window object, if you don't, the window will
// be closed automatically when the JavaScript object is garbage collected.
let mainWindow = null;

const createWindow = () => {
  // , resizable:false
  mainWindow = new BrowserWindow({
    minWidth: 1200,
    minHeight: 650
  });
  mainWindow.loadURL(require('url').format({
    pathname: path.join(__dirname, 'index.html'),
    protocol: 'file:',
    slashes: true
  }));
  mainWindow.webContents.openDevTools();
  mainWindow.on('closed', () => {
    mainWindow = null;
  });
};
app.on('ready', createWindow);
app.on('activate', () => {
  if (mainWindow === null) {
    createWindow();
    
  }
});


// 
// ipcMain.on('load-page', (event, arg) => {
//   mainWindow.loadURL(require('url').format({
//     pathname: path.join(__dirname, arg),
//     protocol: 'file:',
//     slashes: true
//   }))
// });

// var cp = require('child_process');
// var py;
// ipcMain.on('load', (event) => {

//   // console.log(arg)  // prints "ping"
//   // event.sender.send('asynchronous-reply', 'pong')
//   console.log('start');
//   py = cp.exec('python arduino.py');
//   console.log('started');

//   console.log('hi');
//   // py.stdout.pipe(process.stdout);
//   // py.stdout.on('data', (data) => {

//   //   console.log('xxx' + data);
//   //   // mainWindow.webContents.send('ping', data);

//   // });
//   py.on('close', (code) => {
//     console.log(`child process exited with code ${code}`);
//   });
//   console.log('bye');

// });


// Function to convert an Uint8Array to a string
var uint8arrayToString = function(data){
    return String.fromCharCode.apply(null, data);
};



var exec = require('child_process').execFile('python', ['arduino.py']);
exec.stdin.setEncoding('utf-8');
exec.stdin.pipe(process.stdin);

ipcMain.on('com', (event, arg) => {
  // Print 1
  console.log(arg);
  
  exec.stdin.write(arg + "\n");
  // exec.stdin.write("\n");

});

exec.stdout.on('data', (data) => {

    console.log(data);
    // mainWindow.webContents.send('ping', data);

});


app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
    exec.stdin.end();
  }
});