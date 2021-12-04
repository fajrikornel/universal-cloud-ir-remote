// Create storage for the values.
var values = [];

// Get the form element.
var form = document.getElementById('form');

// Add the submit event listener to the form.
form.addEventListener('submit', submit);

function httpGetAsync(theUrl, callback)
{
    var xmlHttp = new XMLHttpRequest();
    xmlHttp.open("GET", theUrl, true); // true for asynchronous 
    xmlHttp.onreadystatechange = function() { 
        if (xmlHttp.readyState == 4 && xmlHttp.status == 200)
            callback(xmlHttp.responseText);
    }
    //xmlHttp.setRequestHeader('Access-Control-Allow-Headers', '*');
    //xmlHttp.setRequestHeader('Access-Control-Allow-Origin', '*');
    xmlHttp.send();
}

function submit(event) {

  // Get the data from the form.
  // event.target represents the form that is being submitted.
  var formData = new FormData(event.target);
  
  // Loop over each pair (name and value) in the form and add it to the values array.
  for (var pair of formData) {
    values.push(pair);
  }
  
  url = 'https://europe-west1-proud-hook-331310.cloudfunctions.net/function-rekam?button=' + pair[1];
  console.log(url);
  httpGetAsync(url)
  
  // Log the values to see the result.
  //console.log(values);
  
  // Prevent the form from default submitting.
  event.preventDefault();

}