const electron = require('electron');
const app = electron.app; // Module to control application life.
const BrowserWindow = electron.BrowserWindow; // Module to create native browser window.
const path = require('path');
const {ipcMain} = require('electron');

require('electron-reload')(__dirname);

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
app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
  }
});
app.on('activate', () => {
  if (mainWindow === null) {
    createWindow();
  }
});

// var cp = require('child_process');

console.log('main')
var py = require('child_process').exec('python arduino.py', (error, stdout, stderr) => {
  console.log('running');
  if (error) {
    console.error(`exec error: ${error}`);
    return;
  }
  console.log(`stdout: ${stdout}`);
  console.log(`stderr: ${stderr}`);
});


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

ipcMain.on('com', (event, arg) => {
  // Print 1
  console.log('com'+arg);
  // console.log(py);
  // Reply on async message from renderer process
  // event.sender.send('async-reply', 2);

  // py.stdout.pipe(process.stdout);
  py.stdout.on('data', (data) => {

    console.log('xxx' + data);
    // mainWindow.webContents.send('ping', data);

  });
  // py.stdin.setEncoding('utf-8');
  // py.stdout.pipe(process.stdout);
  py.stdin.write(arg + '\n');
  py.stdin.end();

});

py.on('close', (code) => {
    console.log(`child process exited with code ${code}`);
  });
console.log('bye');