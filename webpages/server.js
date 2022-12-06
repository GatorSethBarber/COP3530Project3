// Citations for how to set up server:
// https://www.codecademy.com/courses/learn-node-js/lessons/setting-up-a-server-with-http/exercises/http-review
// https://nodejs.org/en/docs/guides/getting-started-guide/
// Heavily influenced by https://www.youtube.com/watch?v=3ZAKY-CDKog

const http = require('http');
const path = require('path');
const fs = require('fs');
const fsPromises = require('fs').promises;
const url = require('url');
const { stringify } = require('querystring');
const testing = require('./testing.js');
const datasetPromise = require('./testing.js')

const PORT = process.env.PORT || 4500;



/**
 * Responsible for serving the basic files involved in making the GUI
 * @param {} filePath The path of the file to get
 * @param {*} contentType The content type of response
 * @param {*} response The response object
 * @param {*} status The status code (defaults to 200)
 * @returns 
 */
const serveFile = async (filePath, contentType, response, status = 200) => {
    try {
        let encoding = 'utf-8';
        if (contentType.includes('image')) {
            encoding = '';
        }
        const rawData = await fsPromises.readFile(filePath, encoding);
        response.writeHead(status, {'Content-Type': contentType});
        // Now, determine what type of data to write
        let data;
        if (contentType === 'application/json') {
            data =JSON.stringify(JSON.parse(rawData));
        }
        else {
            data = rawData;
        }
        return response.end(data);
    } 
    catch (err) {
        console.log(err);
        response.statusCode = 500;  // Server error
        return response.end();
    }
}

/**
 * Handle a query of the data
 * @param {*} req The request
 * @param {*} res The response
 * @returns None
 */
const handleQuery = (req, res) => {
    baseURL = req.url.split('?')[0];
    queryString = req.url.split('?')[1];

    // Write header to the response
    res.writeHead(200, {'Content-Type': 'application/json'});

    // Get the needed fields from the query.
    let splitQuery = new URLSearchParams(queryString);
    const salary = splitQuery.get('salary');
    const education = splitQuery.get('education');
    const experience = splitQuery.get('experience');
    const jobGrowth = splitQuery.get('jobGrowth');
    const useSort = splitQuery.get('useSort');
    
    // Use promises to get the data.
    datasetPromise().then(({Dataset}) => {
        // Create a dataset object (subset of Dataset in Dataset.h)
        let dataset = new Dataset();

        // Read in the data
        let success = dataset.readInData('../dataForProject.csv')
        console.log(success);
        // Rank
        dataset.rankAll(parseInt(salary), parseInt(jobGrowth), parseInt(education), parseInt(experience));
        
        // Perform appropriate sort
        if (useSort == '0')
            dataset.mergeSort();
        else
            dataset.quickSort();
        
        // Send results back to user.
        let results = dataset.getLastN(10);
        let returnResults = [];
        for (let i = 0; i < results.size(); i++) {
            let temp = []
            for (let j = 0; j < results.get(i).size(); j++) {
                temp.push(`${results.get(i).get(j)}`);
            }
            returnResults.push(temp);
        }
        console.log(returnResults);
        res.end(JSON.stringify(returnResults));
    })
    return;
}


// Create a server
const server = http.createServer((req, res) => {
    // For right now, assume only get methods are being passed
    console.log(req.url, req.method);

    // If it is querying for certain data, retrieve it
    if (req.url.includes('?')) {
        return handleQuery(req, res);
    }
    
    // Otherwise, serve the appropriate file
    const extension = path.extname(req.url);
    let contentType;
    switch(extension) {
        case '.css':
            contentType = 'text/css';
            break;
        case '.js':
            contentType = 'text/javascript';
            break;
        case '.json':
            contentType = 'application/json';
            break;
        case '.jpg':
            contentType = 'image/jpeg';
            break;
        case '.png':
            contentType = 'image/png';
            break;
        case '.txt':
            contentType = 'text/plain';
            break;
        case '.wasm':
            contentType = 'application/wasm';
            break;
        default:          // Handles '/' and 'index.html'
            contentType = 'text/html';
    }

    let filePath;
    if (contentType === 'text/html' && req.url === '/') {
        filePath = path.join(__dirname, 'index.html');
    }
    // Need to place the html into their own folder. Then, just add folder name below
    else if (contentType === 'text/html') {
        filePath = path.join(__dirname, req.url);
    }
    else {
        filePath = path.join(__dirname, req.url); // Anything specified in the html files
    }

    // Makes .html extension not required in browser.
    if (!extension && req.url.slice(-1) !== '/') {
        filePath += '.html';
    }

    // See if file actully exists
    const fileExists = fs.existsSync(filePath);

    if (fileExists) {
        // Serve the file
        return serveFile(filePath, contentType, res);
    }
    else {
        // 404 or 301 (redirect)
        console.log(path.parse(filePath));
        return serveFile(path.join(__dirname, '404.html'), 'text/html', res, 404);
    }

});


// Listen for requests
server.listen(PORT, () => {
    console.log(`Server running on port ${PORT}`);
})
