#ifndef CONSTANTS_H
#define CONSTANTS_H
//variable

#define ir_sensor 34

//distance
#define right_distance_pin 12  //8
#define left_distance_pin 13 //7
#define front_distance_pin 14 //4

/*define pin number for encoder*/
#define right_encoder_pin 5 //2
#define left_encoder_pin 18 //3

/*pins for controling the rotation of  motors*/
#define right_forward 27 //10
#define right_backward 26 //9
#define left_forward 32 //25 //6
#define left_backward 33 //33 //5

/*pins for flood_fill_algo*/
#define SIZE 16
#define left_blocked 1
#define front_blocked 2
#define right_blocked 3
#define back_blocked 4
#define back_left_blocked 5
#define right_back_blocked 6
#define front_right_blocked 7
#define front_left_blocked 8
#define right_left_blocked 9
#define front_back_blocked 10
#define right_back_left_blocked 11
#define front_right_back_blocked 12
#define front_right_left_blocked 13
#define front_back_left_blocked 14
#define all_clear 15
#define all_blocked 16

//numeric representation for the orientation of the bot
//visualize like
// front ^
// right >
// back V
// left <
#define bot_right 1
#define bot_left 2
#define bot_front 3
#define bot_back 4


//these numeric values are set to be used in the which cell to
// move next function so it 
#define cell_right 1
#define cell_left 2
#define cell_front 3
#define cell_back 4


#endif