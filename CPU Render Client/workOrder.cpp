#ifndef WORKORDER_T
#define WORKORDER_T

class workOrder_t {

    public:

        //defines the type of work the client is required to do
        //1 = full frame render
        //2 = scan line
        //3 = pixel
        //0 = Null Work, when encountered these work allocations should be ignored
        // -1 = Error, when encountered these work allocations should be ignored
        sf::Int8 workType;
        //This string represents the coordinates of the center point of the current frame
        //for pixel and scan line renders, the work assigned will be determined by the full
        //frame determined by these coordinates, as well as dimensions and zoomFactor
        std::string xCord, yCord;
        //these value determine the width and height of the "frame of reference"
        sf::Uint64 FrameWidth, FrameHeight;
        //this value determines the zoomFactor for the frame of reference upon which the work is to be based
        std::string zoomFactor;
        //Determines the maximum iterations for the work
        sf::Uint64 maximumIterations;

		// Work Identification Number - number assigned to work orders in order to uniquely identify them
		std::string WIN;

        //For type 2 work orders only: specifies whether renders are horizontal or vertical lines from the "frame of reference"
        bool isHorizontal;
        //For type 2 work orders only: specifies the numerical value of the line to be rendered
        sf::Uint64 lineNum;

        //For type 3 work orders only: specifies the coordinates of the pixel to be rendered from the "frame of reference"
        sf::Uint64 pixelX, pixelY;

        //Time as a Unix timestamp that the work order was recieved from the Project Coordination Server
        sf::Uint64 timeReceived;
        //Time as a Unix timestamp that the worker began working on the work order
        sf::Uint64 timeWorkStarted;
        //Time as a Unix timestamp that the worker finished work on the work order
        sf::Uint64 timeWorkFinsished;

        //Finished work will be stored in this variable for transmission back to the Project Coordination Server
        BMP completedWork;

        //counts the number of iterations used to finish the render
        sf::Uint64 totalIterationsUsed;

        //total size of workOrder_t is at minimum 60 Bytes, size varies greatly depending on the length of its string components

        workOrder_t(const workOrder_t& other){
            WIN = other.WIN;
            workType = other.workType;
            xCord = other.xCord;
            yCord = other.yCord;
            FrameWidth = other.FrameWidth;
            FrameHeight = other.FrameHeight;
            zoomFactor = other.zoomFactor;
            maximumIterations = other.maximumIterations;
            lineNum = other.lineNum;
            pixelX = other.pixelX;
            pixelY = other.pixelY;
            timeReceived = other.timeReceived;
            timeWorkStarted = other.timeWorkStarted;
            timeWorkFinsished = other.timeWorkFinsished;
            completedWork = other.completedWork;
        }
        workOrder_t(){
        }
};
#endif
