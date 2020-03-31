# Project Title

Wanhao Duplicator 9 Mk2 upgrade Kit Marin source code

## Getting Started

This code was downloaded from https://github.com/garychen99/D9MK2. It has some changes based on https://www.youtube.com/watch?v=UfDirhQ37GQ and on the new version of BLTouch 3.1 that adds some changes to the Configuration file.

### Prerequisites

You need to download Arduino Ver 1.8.5 , since this code will not compile with the newer Arduino.


### Compiling

Just clone the project and open it up in your Arduino IDE. Open up the file "Marlin.ino" and would upload all the project into the IDE.

```
This 3D printer uses an Arduino Mega processor, so make sure to click in  "tools" menu:

1. Select the  Board "Arduino/Genuino Mega / or Mega 2560"
2. Selct Processor: "ATMega2560 (Mega 2560)"
3. To compile, click on the "Checkmark" button in the top right hand corner or go to "Sketch" -> "Verify/Compile"
```


## Installing
To upload the code into printer you can do it two ways:

1. Uploading directly from Arduino IDE.
2. Generating the binary file and then uploading using CURA.

### Directly from Arduino IDE

1. Make sure the Programmer option under "tools" menu should be: "AVRISP MKII"
2. Port: Select where the board is connected to. (This option is under "tools" menu too.
3.  Click the "Arrow" button in the top right hand corner of the screen or go to "Sketch" -> "Upload" 



### Generate Binary File

1. To generate Binary file, go to "Sketch" -> "Export Compiled Binary". This will generate a compiled binary files stored at the root of the project. 
2. You now can use CURA to upload the firmaware . Use the genrated ".bin" file in the previous step.

## Deployment

Add additional notes about how to deploy this on a live system

## Built With

* [Dropwizard](http://www.dropwizard.io/1.0.2/docs/) - The web framework used
* [Maven](https://maven.apache.org/) - Dependency Management
* [ROME](https://rometools.github.io/rome/) - Used to generate RSS Feeds

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Authors

* **Andres Rangel ** - *Initial work* - 

See also the list of [contributors](https://github.com/your/project/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* This is a fork from https://github.com/garychen99/D9MK2 

