function sendform() {
  var code = document.getElementById("code").value;
  var time = document.getElementById("time").value;
  console.log(code);

  var xmlHttp = new XMLHttpRequest();
  var url = "https://europe-west1-proud-hook-331310.cloudfunctions.net/function-pancar?time=" + time +"&button=" + code;
  console.log(url);
  xmlHttp.open("GET", url, true); // true for asynchronous 
  xmlHttp.onreadystatechange = function () {
    if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
      console.log(xmlHttp.responseText);
  }
  xmlHttp.send();
}

function getdb() {
  var select = document.getElementById("code");

  var xmlHttp = new XMLHttpRequest();
  var url = "https://europe-west1-proud-hook-331310.cloudfunctions.net/function-read-db";
  var obj = "";
  console.log(url);
  xmlHttp.open("GET", url, true); // true for asynchronous 
  xmlHttp.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      obj = JSON.parse(xmlHttp.responseText);

      for (const index in obj) {
        var option = document.createElement("option");
        option.text = obj[index].replace(String.fromCharCode(0,0,0,0),"");
        option.value = obj[index];

        select.appendChild(option);
      }
    }

  }
  xmlHttp.send();
}

getdb();