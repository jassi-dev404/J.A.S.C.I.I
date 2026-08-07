const express = require('express')
const path = require('path')
const app = express();

app.set('views', __dirname)
app.set('view engine', 'ejs')

app.use(express.static(__dirname));

app.get("/", (req, res) => {
  res.render('index')
})

app.listen(6969)