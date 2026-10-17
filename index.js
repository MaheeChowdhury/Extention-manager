//You have to write a Node.js program to clear clutter inside of a directory and organize the contents of that directory into different folders

// for example, these files become:

// 1.  name.jpg
// 2.  name.png
// 3.  this.pdf
// 4.  harry.zip
// 5.  Rohan.zip
// 6.  cat.jpg
// 7.  harry.pdf

// this:
// jpg/name.jpg, jpg/cat/jpg
// png/name.jpg
// pdf/this.pdf pdf/harry.pdf
// zip/harry.zip zip/Rohan.zip

// console.log(fs);
// let files = fs.readdir(__dirname) //While working on module, the __dirname doesn't work
// let files = fs.readdir() //also wrong because we have to give it the whole path
// let files = fs.readdir("C:\\Users\\Administrator\\Desktop\\Small node.js Project>") //this makes promise pending because await isn't used

import fs from "fs/promises"
import fsn from "fs"
import path from "path"

const basepath = "C:\\Users\\Administrator\\Desktop\\Small node.js Project"

let files = await fs.readdir(basepath) //this gets all of the files situated at the given path
// console.log(files);

// let extensions = []
for (const item of files) {
    console.log("running for ", item);
    
    let ext = item.split(".")[item.split(".").length - 1] //this gives the item length's last item which is extension
    // console.log(ext);
    if(ext != "js" && ext != "json" && item.split(".").length > 1){ //item.split(".").length > 1 -- means the extension should not be folder 
        
        if(fsn.existsSync(path.join(basepath, ext))){ //if directory exists
            //Move the file to this directory if its not a js or JSON file
            fs.rename(path.join(basepath, item), path.join(basepath, ext, item)) // then we would just rename the folder
    }
    else { //if extension doesn't exists, then we'll make a directory named of that unavailable extension
        fs.mkdir(ext) // first make the folder and then rename later on
        fs.rename(path.join(basepath, item), path.join(basepath, ext, item))
    }
    // console.log(item);    
}

}