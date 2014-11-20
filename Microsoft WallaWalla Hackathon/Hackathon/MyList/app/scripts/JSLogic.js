//Image section
//Loads in images via sendImageRequest
function loadImages(numberOfImages, idValue, entity, elementName) {
    for (var i = 1; i <= numberOfImages; i++) {
        var eName = elementName + i;
        sendImageRequest(numberOfImages, idValue, i, entity, eName);
    }
}

function processCustomerImage(elementId) {
    var customerId = document.getElementById(elementId).value;
    loadImages(1, customerId, 'Customer', 'image');
    // To Load Posting Images use the following code:
    // Form Image 1: loadImage(1, postingId, 'Posting', 'image');
    // Form Image 2: loadImage(2, postingId, 'Posting', 'image');
    // Form Image 3: loadImage(3, postingId, 'Posting', 'image');
    // Form Image 4: loadImage(4, postingId, 'Posting', 'image');
}

//send the image request to the (server?)
function sendImageRequest(nmberOfImages, idValue, i, entity, elementName) {
    var uri;
    if (entity == "Customer")
        uri = 'api/GetImageFile.aspx?customerId=' + idValue;
    else if (entity == "Posting")
        uri = 'api/GetImageFile.aspx?listingId=' + idValue + "&imageNumber=" + i;
    else
        alert("Wrong entity for loadImages.  The function only supports 'Customer' or 'Posting' values.");

    var req1 = new XMLHttpRequest();
    req1.onreadystatechange = function () {
        if (req1.readyState == 4 && req1.status == 200) {
            var binaryOutput = req1.response;
            createImg(binaryOutput, req1.indexName);
        }
    }
    req1.indexName = elementName;
    req1.open("GET", uri, true);
    req1.responseType = "blob";
    req1.send();
}
function createImg(imgData, elementId) {
    var imageObj = new Image();
    imageObj.src = URL.createObjectURL(imgData);

    imageObj.onload = function () {
        var imgElement = document.getElementById(elementId);
        if (this.width < this.height) {
            imgElement.style.width = "50px";
            imgElement.style.height = "60px";
            imgElement.style.paddingLeft = "5px";
            imgElement.style.paddingRight = "5px";
        }
        else if (this.width > this.height) {
            imgElement.style.height = "50px";
            imgElement.style.width = "60px";
            imgElement.style.paddingTop = "5px";
            imgElement.style.paddingBottom = "5px";
        }
        imgElement.src = imageObj.src;
    }
}

//Search section
function search() {
    var textField = document.getElementById("searchText");
    var resultField = document.getElementById("resultContainer");
    resultField.innerHTML = textField.value;
}

function clearField(text) {
    var textField = document.getElementById(text);
    textField.value = "";
    textField.style.color = "black";
}

//Miscellanious functions
function add() {
    var a = document.getElementById("addText1");
    var b = document.getElementById("addText2");
    var result = document.getElementById("resultContainer");

    //Grab the values
    a = a.value;
    b = b.value;
    
    //Parsing
    a = parseInt(a);
    b = parseInt(b);
    result.innerHTML = (a + b).toString();
}

function createTable(resultObj) {
    var tableObj = document.getElementById('tableList');
    for (var i = 0; i < resultObj.length; i++) {
        var trObj = document.createElement('tr');

        //Create cells
        var tdObj1 = document.createElement('td');
        tdObj1.innerHTML = resultObj[i].fname;
        var tdObj2 = document.createElement('td');
        tdObj2.innerHTML = resultObj[i].lname;
        var tdObj3 = document.createElement('td');
        tdObj3.innerHTML = resultObj[i].email;
        var tdObj4 = document.createElement('td');
        tdObj4.innerHTML = resultObj[i].phone;

        //Append cells to row
        trObj.appendChild(tdObj1);
        trObj.appendChild(tdObj2);
        trObj.appendChild(tdObj3);
        trObj.appendChild(tdObj4);
        
        //Append row to table
        tableObj.appendChild(trObj);
    }
}