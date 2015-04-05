var express = require('express')
var app = express()

app.get('/', function (req, res) {
  res.send('Hello World!')
})

app.post('/', function (req, res) {
	console.log('Received: %s', req)

	res.json({"message": "Hello kamiruu"})
})

var server = app.listen(1337, function () {

  var host = server.address().address
  var port = server.address().port

  console.log('Listening at http://%s:%s', host, port)

})