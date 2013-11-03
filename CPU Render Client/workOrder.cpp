#IFNDEF WORKORDER_T
#DEFINE WORKORDER_T

class workOrder_t {

    public:

        //defines the type of work the client is required to do
        //1 = full frame render
        //2 = scan line
        //3 = pixel
        //0 = Null Work, when encountered these work allocations should be ignored
        // -1 = Error, when encountered these work allocations should be ignored
        short int workType;
        //This string represents the coordinates of the center point of the current frame
        //for pixel and scan line renders, the work assigned will be determined by the full
        //frame determined by these coordinates, as well as dimensions and zoomFactor
        string xCord, yCord;
        //these value determine the width and height of the "frame of reference"
        unsigned long long int FrameWidth, FrameHeight;
        //this value determines the zoomFactor for the frame of reference upon which the work is to be based
        string zoomFactor;
        //Determines the maximum iterations for the work
        unsigned long long int maximumIterations;

        //For type 2 work orders only: specifies whether renders are horizontal or vertical lines from the "frame of reference"
        bool isHorizontal;
        //For type 2 work orders only: specifies the numerical value of the line to be rendered
        unsigned long long int lineNum;

        //For type 3 work orders only: specifies the coordinates of the pixel to be rendered from the "frame of reference"
        unsigned long long int pixelX, pixelY;

        //Time as a Unix timestamp that the work order was recieved from the Project Coordination Server
        unsigned long long int timeReceived;
        //Time as a Unix timestamp that the worker began working on the work order
        unsigned long long int timeWorkStarted;
        //Time as a Unix timestamp that the worker finished work on the work order
        unsigned long long int timeWorkFinsished;

        //Finished work will be stored in this variable for transmission back to the Project Coordination Server
        BMP completedWork;

        //counts the number of iterations used to finish the render
        unsigned long long int totalIterationsUsed;

        //total size of workOrder_t is at minimum 60 Bytes, size varies greatly depending on the length of its string components

        workOrder_t(const workOrder_t& other){
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
