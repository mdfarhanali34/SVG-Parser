// Put all onload AJAX calls here, and event listeners
console.log("check");
jQuery(document).ready(function() {
    //On page-load AJAX Example
    jQuery.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/endpoint1',   //The server endpoint we are connecting to
        data: {
            data1: "Value 1",
            data2:1234.56
        },
        success: function (data) {
            /*  Do something with returned object
                Note that what we get is an object, not a string, 
                so we do not need to parse it on the server.
                JavaScript really does handle JSONs seamlessly
            */
            jQuery('#blah').html("On page load, received string '"+data.somethingElse+"' from server");
            //We write the object to the console to show that the request was successful
            console.log(data); 

        },
        fail: function(error) {
            // Non-200 return, do something with error
            $('#blah').html("On page load, received error from server");
            console.log(error); 
        }
    });

    $.ajax({
      type: 'get',
      dataType: 'json',
      url: '/popuateTable',
      data: { 
          fileName: "demo.svg",
          fileSize: "0KB",
          numRect: "0",
          numCirc: "0",
          numPath: "0",
          numGroups: "0"
      },
      success: function (data) {
         
        console.log(data.length);

         for(let i = 0; i < data.length; i++){
          console.log("check");

             console.log("The file name received is :");
             console.log(data[i].fileName); 
             let imgLoc = "./uploads/" + data[i].fileName;
             
             var fileLog = document.getElementById("styled-table");
             let row = fileLog.insertRow(fileLog.rows.length);
             
            
             let imgCell = row.insertCell(0);

             let hrefCell = row.insertCell(1);

             let fsCell = row.insertCell(2);

             let numRCell = row.insertCell(3);

             let numCCell = row.insertCell(4);

             let numPCell = row.insertCell(5);

             let numGCell = row.insertCell(6);

          
             var img = document.createElement('img');

             img.src = imgLoc;

             img.height = 100;

             img.width = 100;

             imgCell.appendChild(img);
             
            
             let link = document.createElement('a');

             let linkText = document.createTextNode(data[i].fileName);

             link.appendChild(linkText);

             link.href = data[i].fileName;

             hrefCell.appendChild(link);

             
             let fsElement = document.createElement('p');

             let fsText = document.createTextNode(data[i].fileSize);

             fsElement.appendChild(fsText);

             fsCell.appendChild(fsElement);

             
             let numRElement = document.createElement('p');

             let numRText = document.createTextNode(data[i].numRect);

             numRElement.appendChild(numRText);

             numRCell.appendChild(numRElement);


             
             let numCElement = document.createElement('p');

             let numCText = document.createTextNode(data[i].numCirc);

             numCElement.appendChild(numCText);

             numCCell.appendChild(numCElement);
              
            
             let numPElement = document.createElement('p');

             let numPText = document.createTextNode(data[i].numPaths);

             numPElement.appendChild(numPText);

             numPCell.appendChild(numPElement);

            
             let numGElement = document.createElement('p');

             let numGText = document.createTextNode(data[i].numGroups);

             numGElement.appendChild(numGText);

             numGCell.appendChild(numGElement);

           
            $('#SVG_View').append('<option value="' + data[i].fileName + '" id="select-svg ' + data[i].fileName + '">' + data[i].fileName + '</option>');

          } 

      },
      fail: function(error) {
          console.log("Error with uploading file names. ");
          console.log(error);
      }
  });


  document.querySelector('#SVG_View').addEventListener("change", function() {
 

    let file = $( "#SVG_View option:selected" ).text();
    console.log(file);

        jQuery.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/svgViewPanel',   //The server endpoint we are connecting to
        data: {
            fileName: file
        },
        success: function (data) {
            
            let table = $('#Panel_table');

            table.empty();
            $('#showAttr').empty();
            $('#showAttr').append('<option value="Welcome">Welcome</option>');


            
            table.append(
                '<tr><td colspan="6" rowspan="2"><img id="imageInFocus" src="' + file + '" width="800px" /></td></tr>' +
                '<tr></tr>'
            );

            table.append("<tr><th>Title</th><th>Description</th></tr>");
            table.append("<tr><td>"+data.title+"</td><td>"+data.description+"</td></tr>");
            table.append("<tr><th>Component</th><th>Summary</th><th>Other attributes</th></tr>");

            let i;
            let select;
            //Loop through rectangles

           // table.append('<tr><td colspan="7"><select id= "showAttr"><option>Please select an component to display their attributes</option></select></td></tr>');


            data.rectangles.forEach(function(r, i)  {
                table.append('<tr><td>Rectangle ' + (i - -1) + '</td><td colspan="4">Top left: x=' + r.x + r.units + ', y=' + r.y + r.units + '<br>' +
                    'Width: ' + r.w + r.units + ' Height: ' + r.h + r.units + '</td><td class="other-attributes">' + r.numAttr + '</td></tr>')
            });      
            
            if (data.rectangles.length > 0) {
                
                select = $('#showAttr');
                for(i = 0; i < data.rectangles.length; i++){
                    select.append('<option value="' + i + '" class="element-option">Rectangle ' + (i - -1) + '</option>');
                }
            }


            data.circles.forEach(function(c, i)  {
                table.append('<tr><td>Circle ' + (i - -1) + '</td><td colspan="4">Center: cx=' + c.cx + c.units + ', cy=' + c.cy + c.units + '<br>' +
                    'Radius: ' + c.r + c.units + '</td><td class="other-attributes">' + c.numAttr + '</td></tr>')
            });

            if (data.circles.length > 0) {
                
                select = $('#showAttr');
                for(i = 0; i < data.circles.length; i++){
                    select.append('<option value="' + i + '" class="element-option">Circle ' + (i - -1) + '</option>');
                }
            }

            data.paths.forEach(function(p, i)  {
                table.append('<tr><td>path ' + (i - -1) + '</td><td colspan="4">data: ' + p.d + '</td><td class="other-attributes">' + p.numAttr + '</td></tr>')
            });   
            
            if (data.paths.length > 0) {
                
                select = $('#showAttr');
                for(i = 0; i < data.paths.length; i++){
                    select.append('<option value="' + i + '" class="element-option">Path ' + (i - -1) + '</option>');
                }
            }

            data.groups.forEach(function(g, i)  {
                table.append('<tr><td>Group ' + (i - -1) + '</td><td colspan="4">Number of children: ' + g.children + '</td><td class="other-attributes">' + g.numAttr + '</td></tr>')
            });

            
        
        },
        fail: function(error) {
            // Non-200 return, do something with error
            $('#blah').html("On page load, received error from server");
            console.log(error); 
        }
    });
 
  });







document.querySelector('#showAttr').addEventListener("change", function() {
    
    let file = $( "#showAttr option:selected" ).text();
    let myArray = file.split(/([0-9]+)/);
    

    const imageName = $('#imageInFocus').attr('src');
    var table = $('#attributeTable');
    jQuery.ajax({
        type: 'get',            //Request type
        dataType: 'json',       //Data type - we will use JSON for almost everything 
        url: '/svgViewPanel',   //The server endpoint we are connecting to
        data: {
            fileName: imageName
        },
        success: function (data) {
      
            
            table.empty();
            table.append('<tr><th class="heading"><h2>Attribute</h2></th><th class="heading"><h2>Value</h2></th></tr>');
        
            let s;
            console.log("check");
            let shapeType = myArray[0];
            console.log(shapeType);
        
            if (shapeType === "Circle ") {
                console.log("hoka");
        
                s = data.circles[myArray[1] -1];
                console.log(s);

                table.append(
                    '<tr><td>cx</td><td>' + s.cx + '</td></tr>' +
                    '<tr><td>cy</td><td>' + s.cy + '</td></tr>' +
                    '<tr><td>r</td><td>' + s.r + '</td></tr>' +
                    '<tr><td>units</td><td>' + s.units + '</td></tr>');
        
                 if (s.numAttr > 0) table.append('<tr><td colspan="2"><b>Other Attribute(s)</b></td></tr>');
                 s.otherAttrs.forEach(function(oa) {
                 table.append(
                         '<tr><td>' + oa.name + '</td><td>' + oa.value + '</td></tr>'
                     )
                 })
            }else if (shapeType === "Rectangle ") {
              s = data.rectangles[myArray[1] -1];
              table.append(
                  '<tr><td>x</td><td>' + s.x + '</td></tr>' +
                  '<tr><td>y</td><td>' + s.y + '</td></tr>' +
                  '<tr><td>width</td><td>' + s.w + '</tr>' +
                  '<tr><td>height</td><td>' + s.h + '</tr>'+
                  '<tr><td>units</td><td>' + s.units + '</tr>');
      
              if (s.numAttr > 0) table.append('<tr><td colspan="2"><b>Other Attribute(s)</b></td></tr>');
              s.otherAttrs.forEach(function(oa) {
                  table.append(
                      '<tr><td>' + oa.name + '</td><td>' + oa.value + '</td></tr>'
                  )
              })
          }else if (shapeType === "Path ") {
            s = data.paths[myArray[1] -1];
            table.append('<tr><td>d</td><td>' + s.d + '</td></tr>');
    
            if (s.numAttr > 0) table.append('<tr><td colspan="2"><b>Other Attribute(s)</b></td></tr>');
            s.otherAttrs.forEach(function(oa) {
                table.append(
                    '<tr><td>' + oa.name + '</td><td>' + oa.value + '</td></tr>'
                )
            })
        }


            console.log(imageName);
        
        },
        fail: function(error) {
            // Non-200 return, do something with error
            $('#blah').html("On page load, received error from server");
            console.log(error); 
        }
    });






});



    /* Add shape */
    $('#addRectangess').submit(function(e) {
        e.preventDefault();
  
        let filename = $( "#SVG_View option:selected" ).text();
        console.log(filename);
  
        let shapeType = "Rectangle";
        console.log(shapeType);
  
        let x = $("#xID").val();
        console.log("\n\nx = " + x);
  
        let y = $("#yID").val();
        console.log("y = " + y);
  
        let rw = $("#rwID").val();
        console.log("r = " + rw);
  
        let h = $("#height").val();
        console.log("r = " + h);
  
        let units = $("#unitsID").val();
        console.log("units = " + units);
  
        if(filename !== "None")
        {
          $.ajax({
            type: 'get',            //Request type
            dataType: 'text',       //Data type - we will use JSON for almost everything
            url: '/addShape/',   //The server endpoint we are connecting to
            data: {
              filename: filename,
              shapeType: shapeType,
              x: x,
              y: y,
              rw: rw,
              h: h,
              units: units
            },
            success: function (data) {
              console.log(data);
              console.log("in success");
              alert("Successfully Added");
              /*Reloads the page to display latest data */
              location.reload();
            },
            fail: function(error) {
  
              alert("Could not add component to " + filename);
              console.log(error);
            }
          });
        }
        else
        {
          alert("Please select a file");
        }
      });


      $('#addCircless').submit(function(e) {
        e.preventDefault();
  
        let filename = $( "#SVG_View option:selected" ).text();
        console.log(filename);
  
        let shapeType = "Circle";
        console.log(shapeType);
  
        let cx = $("#xCirc").val();
        console.log("\n\nx = " + cx);
  
        let cy = $("#yCirc").val();
        console.log("y = " + cy);
  
        let rw = $("#radiusID").val();
        console.log("r = " + rw);
  
        let units = $("#unitsCirc").val();
        console.log("units = " + units);
  
        if(filename !== "None")
        {
          $.ajax({
            type: 'get',            //Request type
            dataType: 'text',       //Data type - we will use JSON for almost everything
            url: '/addCirc/',   //The server endpoint we are connecting to
            data: {
              filename: filename,
              shapeType: shapeType,
              cx: cx,
              cy: cy,
              rw: rw,
              units: units
            },
            success: function (data) {
              console.log(data);
              console.log("in success");
              alert("Successfully Added");
              /*Reloads the page to display latest data */
              location.reload();
            },
            fail: function(error) {
  
              alert("Could not add component to " + filename);
              console.log(error);
            }
          });
        }
        else
        {
          alert("Please select a file");
        }
      });
    

      $('#scaleShapeRect').submit(function(e) {
        e.preventDefault();

        let filename = $( "#SVG_View option:selected" ).text();
        console.log(filename);
  

  
        let scaleFactor = $("#scaleRect").val();
        console.log("scale Factor is = " + scaleFactor);
  
        if(filename !== "None")
        {
          $.ajax({
            type: 'get',            //Request type
            dataType: 'text',       //Data type - we will use JSON for almost everything
            url: '/scaleShapeRect/',   //The server endpoint we are connecting to
            data: {
              filename: filename,
              scaleFactor: scaleFactor,
            },
            success: function (data) {
              console.log(data);
              console.log("in success");
              alert("Successfully Scaled Shape");
              /*Reloads the page to display latest data */
              location.reload();
            },
            fail: function(error) {
  
              alert("Could not add component to " + filename);
              console.log(error);
            }
          });
        }
        else
        {
          alert("Please select a file");
        }
      });

      $('#scaleShapeCirclre').submit(function(e) {
        e.preventDefault();

        let filename = $( "#SVG_View option:selected" ).text();
        console.log(filename);
  

  
        let scaleFactor = $("#scaleCir").val();
        console.log("scale Factor is = " + scaleFactor);
  
        if(filename !== "None")
        {
          $.ajax({
            type: 'get',            //Request type
            dataType: 'text',       //Data type - we will use JSON for almost everything
            url: '/scaleShapeCircle/',   //The server endpoint we are connecting to
            data: {
              filename: filename,
              scaleFactor: scaleFactor,
            },
            success: function (data) {
              console.log(data);
              console.log("in success");
              alert("Successfully Scaled Shape");
              /*Reloads the page to display latest data */
              location.reload();
            },
            fail: function(error) {
  
              alert("Could not add component to " + filename);
              console.log(error);
            }
          });
        }
        else
        {
          alert("Please select a file");
        }
      });


      $('#form').submit(function(e) {
        
        e.preventDefault();
        var file = $( "#showAttr option:selected" ).text();
        var myArray = file.split(/([0-9]+)/);

        var checkFile = $( "#SVG_View option:selected" ).text();

        //console.log(file + "special one");
        
        var attrName = document.getElementById("fname").value;
        
        
        var attrNameVal = document.getElementById("lname").value;
        console.log(attrName);
        console.log(attrNameVal);
        
        var indie = document.getElementById("shapeName").value;
        
        //parseInt(myArray[1]);
        
        console.log(indie);
        
        var holder =  parseInt(document.getElementById("shapeValue").value);
        
        console.log(holder);
        
        var elem;
        
        if(myArray[0] === "Rectangle " ){
        
            elem = "rect";
        
        }else if(myArray[0] === "Circle "){
            elem = "circ";
        }else if(myArray[0] === "Path "){
            elem = "path";
        }else if(myArray[0] === "Group "){
            elem = "group";
        }
        
        
        
        console.log(elem);
        
        
        
        let elementObj = {
            elemType: elem,
            index: holder,
            fileName: checkFile,
            attr: attrName,
            attrValue: attrNameVal
          }
        
           // elementObj = JSON.stringify(elementObj);
           
            console.log(elementObj);
        
        
            $.ajax({
                type: 'get',            //Request type
                dataType: 'json',       //Data type - we will use JSON for almost everything 
                url: '/updatePanel',   //The server endpoint we are connecting to
                data:
                {
                elementObj
                },
                success: function (data) {
              
                    alert("Successfully eddited");
                        location.reload(true);
                
                },
                fail: function(error) {
                    // Non-200 return, do something with error
                    $('#blah').html("On page load, received error from server");
                    console.log(error); 
                }
            });        

      });



      
    // To Create a new SVG
    $('#createSVGForm').submit(function(e){
      console.log("client check");
      e.preventDefault();
      let newFileName = $('#newSVGName').val();
      let title = $('#newTitle').val();
      let description = $('#newDescription').val();
      $.ajax({
          type: 'get',            
          dataType: 'json',       
          url: '/createSVGImage',
          data: {
              fileName: newFileName,
              title: title,
              description: description
          },
          success: function (creationData) {
              
              location.reload(true);
              alert("Sucesfully created a file!!");
              
              // alert(creationData.status);
          },
          fail: function(error) {
              console.log(error); 
          }
      });
  });


  $('#tits').submit(function(e){

    e.preventDefault();
    console.log("client check");
    
    const title = $('#newTits').val();

    const imageName = $( "#SVG_View option:selected" ).text();
    $.ajax({
        type: 'get',
        dataType: 'json',
        url: '/saveTitle',
        data: {
            imageName: imageName,
            title: title
        },
        success: function () {

            alert("Title saved!");
            location.reload(true);
        },
        fail: function (error) {
            alert(new Error("Could not save description. " + error));
        }
    });
});

$('#descs').submit(function(e){

  e.preventDefault();
  const description = $('#newDesc').val();
  const imageName = $( "#SVG_View option:selected" ).text();
  $.ajax({
      type: 'get',
      dataType: 'json',
      url: '/saveDesc',
      data: {
          imageName: imageName,
          description: description
      },
      success: function () {
          alert("Description saved!");
          location.reload(true);
      },
      fail: function (error) {
          alert(new Error("Could not save description. " + error));
      }
  });
});


});