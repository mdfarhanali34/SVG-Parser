'use strict'

// C library API
const ffi = require('ffi-napi');

// Express App (Routes)
const express = require("express");
const app     = express();
const path    = require("path");
const fileUpload = require('express-fileupload');

app.use(fileUpload());
app.use(express.static(path.join(__dirname+'/uploads')));

// Minimization
const fs = require('fs');
const JavaScriptObfuscator = require('javascript-obfuscator');
const { rejects } = require('assert');
const { json } = require('express');

// Important, pass in port as in `npm run dev 1234`, do not change
const portNum = process.argv[2];

// Send HTML at root, do not change
app.get('/',function(req,res){
  res.sendFile(path.join(__dirname+'/public/index.html'));
});

// Send Style, do not change
app.get('/style.css',function(req,res){
  //Feel free to change the contents of style.css to prettify your Web app
  res.sendFile(path.join(__dirname+'/public/style.css'));
});

// Send obfuscated JS, do not change
app.get('/index.js',function(req,res){
  fs.readFile(path.join(__dirname+'/public/index.js'), 'utf8', function(err, contents) {
    const minimizedContents = JavaScriptObfuscator.obfuscate(contents, {compact: true, controlFlowFlattening: true});
    res.contentType('application/javascript');
    res.send(minimizedContents._obfuscatedCode);
  });
});

let sharedLib = ffi.Library('parser/bin/libsvgparser.so',{

  'SVGtoJSON_FFI': ['string', ['string']],
  'fullImgToJSON': ['string', ['string']],
  'addRectangle': ['void', ['string','string','float','float','float','float','string']],
  'addCircle': ['void', ['string','string','float','float','float','string']],
  'scaleRect': [ 'void', ['string', 'string']],
  'scaleCircle': [ 'void', ['string', 'string']],
  'updateOtherAttribute': ['string', ['string', 'string', 'float', 'string', 'string']],
  'createNewSVGFile': [ 'string', ['string', 'string', 'string']],
  'saveTitle': ['bool', ['string', 'string']],
  'saveDesc': ['bool', ['string', 'string']],
  'validateFile': ['bool', ['string']]
  
});



app.post('/upload', function(req, res) {
  if(!req.files) {
    return res.status(400).send('No files were uploaded.');
  }

  let uploadFile = req.files.uploadFile;

  // Use the mv() method to place the file somewhere on your server
  uploadFile.mv('uploads/' + uploadFile.name, function(err) {
    if(err){
      //If the file saving errored
      return res.status(500).send(err);
    } else {
      //Check if the file is valid
      if (sharedLib.validateFile('uploads/' + uploadFile.name)) {
        res.redirect('/');
      } else {
        fs.unlinkSync('uploads/' + uploadFile.name);
        return res.status(400).send("Invalid file.");
      }
    }
  });
});

//Respond to GET requests for files in the uploads/ directory
app.get('/uploads/:name', function(req , res){
  fs.stat('uploads/' + req.params.name, function(err, stat) {
    if(err == null) {
      res.sendFile(path.join(__dirname+'/uploads/' + req.params.name));
    } else {
      console.log('Error in file downloading route: '+err);
      res.send('');
    }
  });
});

//******************** Your code goes here ******************** 
app.listen(portNum);
console.log('Running app at localhost: ' + portNum);


//Sample

app.get('/endpoint1', function(req , res){
  let retStr = req.query.data1 + " " + req.query.data2;
 
  res.send(
    {
      somethingElse: retStr
    }
  );
});



console.log("okkkk");
console.log("test 2");
app.get('/updatePanel', function (req, res) {

  console.log("okkkk");

  console.log(req.query);


  console.log("okkkk");
  
  var attrName = req.query.elementObj.attr;
  var attrVal = req.query.elementObj.attrValue;
  var elem = req.query.elementObj.elemType;
  var index = req.query.elementObj.index;
  var file = __dirname + "/uploads/" + req.query.elementObj.fileName;

    console.log(index);
    console.log(attrName);



  try {

    console.log("Attribute name: " + attrName);
     console.log("Attribute value: " + attrVal);
     console.log("Element is: " + elem);
     console.log("Element index is: " + index);
     console.log("File targeted is: " + file);
    
    var returnVal = sharedLib.updateOtherAttribute(file, elem, index, attrName, attrVal);

    returnVal = JSON.parse(returnVal);

    console.log(returnVal);

    if (returnVal == true) { // updated and valid
      res.send(true);
      
    } else { // didn't update cuz invalid
      res.send(false);
     
    }

  } catch (err) {
    console.log("Error in updateOtherAttrs. Err: " + err);
    return res.status(500).send(err);
  }

});

//Sample endpoint
app.get('/popuateTable', function(req , res){


  const fs = require('fs');
  const files = fs.readdirSync('uploads');
  
  var arr = [];

  files.forEach(file => {
    
    let path = "uploads/" + file;

    let descJSON = sharedLib.SVGtoJSON_FFI(path);
    let hula = JSON.parse(descJSON);
   // console.log(hula);
    //console.log(hula.numCirc);
    let fileSize = Math.round(fs.statSync("uploads/" + file).size / 1024);

    let updatedJson = {

      fileName: file,
      fileSize: fileSize,
      numRect: hula.numRect,
      numCirc: hula.numCirc,
      numPaths: hula.numPaths,
      numGroups: hula.numGroups
    };

    arr.push(updatedJson);
    
  });

 // console.log(arr);
  res.send(
    
      arr
    
  );

});



// SVG VIEW PANEL
app.get('/svgViewPanel', function(req , res){

  let result = sharedLib.fullImgToJSON("uploads/" + req.query.fileName);
   //console.log(result);
  res.send(result);

});

app.get('/addShape', function(req , res){
  let file = req.query.filename;
  console.log("\n\n File Name received is: " + file + "\n\n");

  console.log("shapeType: "+req.query.shapeType);
  console.log("x: "+req.query.x);
  console.log("y: "+req.query.y);
  console.log("rw: "+req.query.rw);
  console.log("h: "+req.query.h);
  console.log("units: "+req.query.units);

  let addShapeExecute = sharedLib.addRectangle(req.query.filename, req.query.shapeType, parseFloat(req.query.x), parseFloat(req.query.y), parseFloat(req.query.rw), parseFloat(req.query.h), req.query.units );

  res.send("Successfully Added");

});

app.get('/addCirc', function(req , res){

  let file = req.query.filename;
  console.log("\n\n File Name received is: " + file + "\n\n");

  console.log("shapeType: "+req.query.shapeType);
  console.log("cx: "+req.query.cx);
  console.log("cy: "+req.query.cy);
  console.log("rw: "+req.query.rw);
  console.log("units: "+req.query.units);

  let addShapeExecute = sharedLib.addCircle(req.query.filename, req.query.shapeType, parseFloat(req.query.cx), parseFloat(req.query.cy), parseFloat(req.query.rw), req.query.units );

  res.send("Successfully Added");

  
});

/* Scale Shapes */
app.get('/scaleShapeRect', function(req , res){
  console.log("Scale Shape Data Received:");
  console.log("\n\n File Name : " + req.query.filename);
  console.log("scale Factor: "+req.query.scaleFactor);

  let scaleExecute = sharedLib.scaleRect(req.query.filename, String(req.query.scaleFactor));

  res.send("Successfully Added");
});

/* Scale Shapes */
app.get('/scaleShapeCircle', function(req , res){
  console.log("Scale Shape Data Received:");
  console.log("\n\n File Name : " + req.query.filename);
  console.log("scale Factor: "+req.query.scaleFactor);

  let scaleExecute = sharedLib.scaleCircle(req.query.filename, String(req.query.scaleFactor));

  res.send("Successfully Added");
});




// Create SVG Image
app.get('/createSVGImage', async function(req, res) {

  let initialFilename = req.query.fileName;

  
  let file = "uploads/" + initialFilename + "";
  let title = req.query.title;
  let description = req.query.description;

  console.log("\n\n File Name received is: " + file + "\n\n");
  console.log("\n\n Title = " + title + " and description = " + description);

    var jsonObj = sharedLib.createNewSVGFile(file, title, description);
    console.log("\n\n" + jsonObj + "\n\n");


   res.send(jsonObj);

});

app.get('/saveTitle', function(req, res) {

  console.log(req.query.imageName);
  console.log(req.query.title);
 
  const result = sharedLib.saveTitle("uploads/" + req.query.imageName, req.query.title);

console.log(result);

  if (result) {
    res.send(true);
  } else {
    res.send(false);
  }
});

app.get('/saveDesc', function(req, res) {

  const result =  sharedLib.saveDesc("uploads/" + req.query.imageName, req.query.description);
  if (result) {
    res.send(true);
  } else {
    res.send(false);
  }
});