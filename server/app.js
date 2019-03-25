const express = require("express");

const app = express();
const port = 8080;
const dir = "../docs/";

app.use(express.static(dir));
app.listen(port, () => console.log(`serving '${dir}' directory on ${port}`));
