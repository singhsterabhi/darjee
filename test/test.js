const $ = require('jquery');
// var enabled = false;
// Use require to add webcamjs
// const WebCamera = require("webcamjs");
const {ipcRenderer} = require('electron');

const comandlist = {
  'checkconnection': 'A',
  'checkbutton': 'B',
  'forcesensor': 'F',
  'gyroscope': 'G',
  'home': 'H',
  'reddisplay': 'I',
  'greendisplay': 'J',
  'bluedisplay': 'K',
  'motorm1': 'L',
  'motorm2': 'M',
  'endeffectorstepper': 'N',
  'motionxy': 'O',
  'readpressure': 'P',
  'forwardx': 'XF',
  'backwardX': 'X'
};

// WebCamera.set( 'constraints', {
// 	facingMode: { exact: "user" }
// } );

// function startcam() {
//   if (!enabled) { // Start the camera !
//     enabled = true;
//     WebCamera.attach('#cam');
//     console.log("The camera has been started");
//   } else { // Disable the camera !
//     enabled = false;
//     WebCamera.reset();
//     console.log("The camera has been disabled");
//   }

// }

// startcam();

// ipcRenderer.send('load');

function serialsend() {
  var comm = $('.input').val();
  ipcRenderer.send('com', comm);
}
