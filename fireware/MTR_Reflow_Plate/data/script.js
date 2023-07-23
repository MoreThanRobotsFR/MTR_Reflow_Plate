/*
Name: MTR Reflow Plate
Version: 1.0
Description: Script for the MTR Reflow Plate
Plateform: ESP32 DevKit V1
Author: Ciciliano Altmann (MTR)
Date: 23/07/2023
License: MIT License
*/

function sendData(){
    var preheatingTime = $("#preheatingTime").val();
    var preheatingTemperature = $("#preheatingTemperature").val();
    var recirculationTime = $("#recirculationTime").val();
    var recirculationTemperature = $("#recirculationTemperature").val();
    var reflowTime = $("#reflowTime").val();
    var reflowTemperature = $("#reflowTemperature").val();
    var Z4 = $("#Z4").val();
    var coolingTemperature = $("#coolingTemperature").val();
    
    $.ajax({
        url: "/params",
        method: "POST",
        data: {
            temps_zone_preheating: preheatingTime*1000, 
            temperature_zone_preheating: preheatingTemperature, 
            temps_zone_recirculation: recirculationTime*1000, 
            temperature_zone_recirculation: recirculationTemperature, 
            temps_zone_reflow: reflowTime*1000, 
            temperature_zone_reflow: reflowTemperature, 
            temps_zone_cooling: Z4, 
            temperature_zone_cooling: coolingTemperature
        }
    });
}

function fetchData() {
    var div = document.getElementById('json-display');
    div.innerHTML = '';  // Clear the previous data
      
    fetch('/getParams')  // Replace this URL with the actual URL to fetch your dynamic JSON.
        .then(response => response.json())
        .then(data => {
            let content = `
                <h3 class="w3-padding">Paramètres actuels :</h3>
                <p class="w3-xxlarge">
                  Preheating : 
                  <span>${data.temps_zone_preheating / 1000}</span> secondes à 
                  <span>${data.temperature_zone_preheating}</span>°C
                </p>
                <p class="w3-xxlarge">
                  Recirculation :
                  <span>${data.temps_zone_recirculation / 1000}</span> secondes à 
                  <span>${data.temperature_zone_recirculation}</span>°C
                </p>
                <p class="w3-xxlarge">
                  Reflow : 
                  <span>${data.temps_zone_reflow / 1000}</span> secondes à 
                  <span>${data.temperature_zone_reflow}</span>°C
                </p>
                <p class="w3-xxlarge">Cooling : <span>${data.temperature_zone_cooling}</span>°C</p>
                <button onclick="fetchData()" class="w3-btn w3-large w3-ios-grey w3-hover-light-blue w3-margin-top w3-round" style="width:20%">Refresh</button>`;

            div.insertAdjacentHTML('beforeend', content);
        })
        .catch(error => console.error(error));
}

setInterval(function getData() {
    var xhttp = new XMLHttpRequest();

    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            document.getElementById("valeurTemperature").innerHTML = this.responseText;
            
        }
    };

    xhttp.open("GET", "readTemperature", true);
    xhttp.send();
}, 2000);

function startButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "start", true);
    xhttp.send();
}

function stopButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "stop", true);
    xhttp.send();
}

function manuButton() {
    window.location.href = "manu";

    var startStopManu = 2;
    
    $.ajax({
        url: "/manu",
        method: "POST",
        data: {
            manuMode: startStopManu
        }
    });
    
  }

function sendManuTemperature(){
    var manuTemperature = $("#manuTemperature").val();
    
    $.ajax({
        url: "/manuSetTemperature",
        method: "POST",
        data: {
            manuTemperature: manuTemperature
        }
    });
}

function manuStartButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "manuStart", true);
    xhttp.send();
}

function manuStopButton() {
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "manuStop", true);
    xhttp.send();
}

function chartButton() {
    window.location.href = "chart";
}