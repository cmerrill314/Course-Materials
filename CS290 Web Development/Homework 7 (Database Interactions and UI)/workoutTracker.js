/*
Christopher Merrill 
CS290
5/30/2017
HW Assignment: Database Interactions and UI

Description: This file contains all of the server side interations for the Workout Tracker

Sources: All of the routes are based off the routes in the course lectures, 
but they have been modified for this specific database
*/

var express = require('express');
var handlebars = require('express-handlebars').create({defaultLayout:'main'});
var bodyParser = require('body-parser');
var app = express();
var mysql = require('mysql');

//Create a new pool
var pool = mysql.createPool({
  host  : 'classmysql.engr.oregonstate.edu',
  user  : 'cs290_merrillc',
  password: '2710',
  database: 'cs290_merrillc'
});

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(express.static('public')); 

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 8386);

//Render home.handlebars when the user visits the page
app.get('/',function(req,res){
  res.render('home');
});

//This allows the user to view the current status of their workout database
app.get('/select-table', function(req, res, next) {
	var context = {};
	pool.query('SELECT * FROM workouts', function(err, rows, fields){
		if(err) {
			next(err);
			return;
		}
		//Send the JSON results back as a string, they will be parsed and assembled client-side
		context.results = JSON.stringify(rows);		
		res.send(context.results); 
	});
});

//This allows the user to add a new workout to the database
app.get('/insert', function(req, res, next) {
	var context = {};
	pool.query("INSERT INTO workouts (`name`, `reps`, `weight`, `date`, `lbs`) VALUES (?, ?, ?, ?, ?)", [req.query.name, req.query.reps, req.query.weight, req.query.date, req.query.lbs], function(err, result){
		if(err) {
			next(err);
			return;
		}
	});
	context.results = "Row Inserted";
	res.send(context.results);  
});

//This allows the user to update an existing row in the database
app.get('/update',function(req,res,next){
  var context = {};
  pool.query("SELECT * FROM workouts WHERE id=?", [req.query.id], function(err, result){
    if(err){
      next(err);
      return;
    }
    if(result.length == 1){
      var curVals = result[0];
      pool.query("UPDATE workouts SET name=?, reps=?, weight=?, date=?, lbs=? WHERE id=? ",
        [req.query.name || curVals.name, req.query.reps || curVals.reps, req.query.weight || curVals.weight, req.query.date || curVals.date, req.query.lbs || curVals.lbs, req.query.id],
        function(err, result){
        if(err){
          next(err);
          return;
        }
        context.results = "Row Updated";
        res.send(context.results); 
      });
    }
  });
});

//This allows the user to delete a row in the database
app.get('/delete',function(req,res,next){
  var context = {};
  pool.query("DELETE FROM workouts WHERE id=?", [req.query.id], function(err, result){
    if(err){
      next(err);
      return;
    }
    context.results = "Row Deleted";
	res.send(context.results);  
  });
});

//This code initializes a new database called "workouts"
app.get('/reset-table',function(req,res,next){
  var context = {};
  pool.query("DROP TABLE IF EXISTS workouts", function(err){ 
    var createString = "CREATE TABLE workouts("+
    "id INT PRIMARY KEY AUTO_INCREMENT,"+
    "name VARCHAR(255) NOT NULL,"+
    "reps INT,"+
    "weight INT,"+
    "date DATE,"+
    "lbs BOOLEAN)";
    pool.query(createString, function(err){
      context.results = "Table reset";
	  res.send(context.results);
    })
  });
});

app.use(function(req,res){
  res.status(404);
  res.render('404');
});

app.use(function(err, req, res, next){
  console.error(err.stack);
  res.type('plain/text');
  res.status(500);
  res.render('500');
});

app.listen(app.get('port'), function(){
  console.log('Express started on http://flip2.engr.oregonstate.edu:' + app.get('port') + '; press Ctrl-C to terminate.');
});