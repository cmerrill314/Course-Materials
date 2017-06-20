/*JavaScript for Chris Merrill's OpenWeatherMap API application*/

var apiKey = 'fa7d80c48643dfadde2cced1b1be6ca1';
document.addEventListener('DOMContentLoaded', bindButtons);

function bindButtons(){
	//The following function defines the behavior of form 1's "submit" button
	document.getElementById('submitForm1').addEventListener('click', function(event){
		var req = new XMLHttpRequest();                        
		var url = "";                                          
		var zipValue = document.getElementById('zip').value;   
		var cityValue = document.getElementById('city').value; 
		
		//Update the URL to include the user-entered zip code or city value in the OpenWeatherMap API
		if(zipValue != "")
			url = "http://api.openweathermap.org/data/2.5/weather?units=imperial&zip=" + zipValue + ",us&appid="  + apiKey;
		else if(cityValue != "")
			url = "http://api.openweathermap.org/data/2.5/weather?units=imperial&q=" + cityValue + "&appid="  + apiKey;
		
		req.open("GET", url, false); 
		
		//Asynchronous Call:
		req.addEventListener('load',function(){
			if(req.status >= 200 && req.status < 400){
				var response = JSON.parse(req.responseText);
				//Post Data to the "results" section of the page
				document.getElementById('cityName').textContent = response.name;
				document.getElementById('temp').textContent = response.main.temp + " F";
				document.getElementById('pressure').textContent = response.main.pressure + " hPa";
				document.getElementById('humidity').textContent = response.main.humidity + "%";
			} 
			else {
				console.log("Error in network request: " + req.statusText);
			}});	
		req.send(null);
		event.preventDefault(); 
	})
	
	//The following function defines the behavior of form 2's "submit" button
	document.getElementById('submitForm2').addEventListener('click', function(event){
		var req = new XMLHttpRequest();
		var payload = {text:null};
		payload.text = document.getElementById('text1').value;
		req.open('POST', "http://httpbin.org/post", true);
		
		//Asynchronous Call:
		req.setRequestHeader('Content-Type', 'application/json');
		req.addEventListener('load',function(){
		  if(req.status >= 200 && req.status < 400){
			//Display the response, which should be the same as the entered text
			var response = JSON.parse(req.responseText);
			var response2 = JSON.parse(response["data"]); //Parse the data section of the response to access the text
			document.getElementById('text2').textContent = response2["text"];
		  } else {
			console.log("Error in network request: " + req.statusText);
		  }});
		req.send(JSON.stringify(payload));
		event.preventDefault();
  });
}