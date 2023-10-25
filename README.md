# Catbot_tools
Repository for a variety of Catbot Related tools stored in different branches /releases

## Development
See `template-project` folder for the proper format.

* Things you must change from the template
  - Change the name of the project folder from 'template-project' to something descriptive
  - Fill out the README.md with information about your project/feature
* Not recommened but things you can change from the template
  - Move the python file outside of the raspi folder if there is no arduino code
  - rename the raspi folder
  - rename the arduino folder**
  - rename the main python file
  - rename the main arduino file**
  These changes must be written clearly in the README.md
  ** = you must also rename your main arduino file to the same name as the folder
* Things you can not change from the template
  - The folder structure (all of the code must be within your project folder)
  - The structure of the README.md (you can add more information but you can not remove any of the required information)
  - Code from other projects/features (you can copy code but you can not edit code from other projects/features)

## Reasons for the template
The template is designed to be easy to follow and be organized and also allows for integration with the catbot cli.
> example: `catbot start -D -p template-project` will run the main python file in the template-project folder and catbotuser can use this command without extra configuration.

Readme file is also designed to make it easy to keep track of what the features do and how to use them.
The date and author fields are also designed to add accountability in the case of an updated hardware design. 
The date can be used to determine if the code is compatible with the new hardware design and if needed, the author can be contacted to determine if the code is compatible with the new hardware design.
