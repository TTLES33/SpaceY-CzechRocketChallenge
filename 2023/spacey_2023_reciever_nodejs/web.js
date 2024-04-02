var message_telo = "1-0-0-0-0";
var message_spicka = "0-0-0-0-0";

function makeRequest() {
    httpRequest = new XMLHttpRequest();

    if (!httpRequest) {
      alert("Giving up :( Cannot create an XMLHTTP instance");
      return false;
    }
    httpRequest.onreadystatechange = alertContents;
    httpRequest.open("GET", "/data");
    httpRequest.send();
  }

  function alertContents() {
    if (httpRequest.readyState === XMLHttpRequest.DONE) {
      if (httpRequest.status === 200) {
        console.log(JSON.parse(httpRequest.responseText));
        message_spicka = JSON.parse(httpRequest.responseText).message_spicka;
        message_telo = JSON.parse(httpRequest.responseText).message_telo;
      } else {
        alert("There was a problem with the request.");
      }
    }
  }
  var intervalId = window.setInterval(function(){
    makeRequest();
    updatedata();
  }, 1000);

  function updatedata(){
    var splitted_telo = message_telo.split("-");
    document.getElementById("gps_1").innerHTML = splitted_telo[1] + " " + splitted_telo[2];
    document.getElementById("gps_1").onclick = function(){
        window.open("https://mapy.cz/?source=coor&id=" + splitted_telo[2] + "%2C" + splitted_telo[1]); 
    }
    document.getElementById("gps_update_1").innerHTML = splitted_telo[3] ;
    document.getElementById("Hmax1").innerHTML = splitted_telo[4] ;
    document.getElementById("radio_update_1").innerHTML = splitted_telo[5] ;

    var splitted_spicka = message_spicka.split("-");
    document.getElementById("gps_0").innerHTML = splitted_spicka[1] + " " + splitted_spicka[2];
    document.getElementById("gps_0").onclick = function(){
        window.open("https://mapy.cz/?source=coor&id=" + splitted_spicka[2] + "%2C" + splitted_spicka[1]); 
    }
    document.getElementById("gps_update_0").innerHTML = splitted_spicka[3] ;
    document.getElementById("radio_update_0").innerHTML = splitted_spicka[5] ;
  }