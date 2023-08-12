#include "Physics.h"


Physics::Physics(vector<Ball> b, float dt_, Uint32 lastU)
{
    balls = b;
    dt = dt_;
    lastUpdate = lastU;

  

}

Physics::Physics() = default;

void Physics::setBalls(vector<Ball> b) 
{
    balls = b;
}

vector<Ball> Physics::getBalls(){
    return balls;
}

void Physics::setDt(float dt_)
{
    dt = dt_;
}
float Physics::getDt(){
    return dt;
}

void Physics::setLastUpdate(Uint32 time){
    lastUpdate = time;
}

Uint32 Physics::getLastUpdate(){
    return lastUpdate;
}




/*  Updates every ball in the simulation and the progression of time

    @param  map   The map of the game

    @return balls   Returns the vector that contains updated balls      

    Time Complexity : O(n^2)  Quadratic time
    Space Complexity : O(n)   Linear Space


*/


vector<Ball> Physics::updateBall( const Map& map)
{   

    // Calculating how much time has past since last physics update
    Uint32 current = SDL_GetTicks();
    float dT = (current - lastUpdate) / 1000.0f;
    setDt(dT);

    for(auto& ball : balls){  // Looping through all the balls in the sim
        
        //cout << "current: " << current << " dt : " << dt << endl;
        //SDL_Delay(1.0f);
    
        // Updating the values of the ball

        float newX = ball.getX() + ball.getVx() * dt;
        float newY = ball.getY() + ball.getVy() * dt;
        ball.setPosition(newX, newY);

        float newAx =  -ball.getVx() * 0.8f ;  // Applying drag and gravity forces
        float newAy =  -ball.getVy() * 0.8f + gravity;
        ball.setAcceleration(newAx, newAy);

        float newVx = ball.getVx() + ball.getAx() * dt;
        float newVy = ball.getVy() + ball.getAy() * dt;
        ball.setVelocity(newVx,newVy);

    
        // Stopping the ball if its velocity is below stability constraint so that it does not move forever
        
        if (fabs(ball.getVx()* ball.getVx() + ball.getVy() * ball.getVy())  < vStable)
        {
            ball.setVelocity(0.0f,0.0f);

        }

        // Looping through the walls to check if they are colliding with the ball,
        // resolving the collision if it is.
        const vector<Wall>& walls = map.getWalls();
        for (const auto& wall : walls) {
            if(checkCollision(ball,wall)){
                resolveCollision();
            }    
        }
        setLastUpdate(current);  // Updating the time of the last physics update

    vecCollidingObjects.clear();  
    
    
    }
    return balls;  // Returning the balls to the game 
}

/*  
    Checks if a collision occurs between a Wall and a Ball
    @param  ball  The ball to be checked.
    @param  wall  The wall to be checked.

    @return  True if collision occurs, False if not.
    
    Time Complexity : O(1) Constant Time
    Space Complexity : O(1) Constant Space
    


*/

bool Physics::checkCollision( Ball& ball, const Wall& wall){
    
    float startX = wall.getStartX();
    float startY = wall.getStartY();
    float endX = wall.getEndX();
    float endY = wall.getEndY();
    float normalX = wall.getNormalX();
    float normalY = wall.getNormalY();
    float wallRadius = wall.getRadius();
    //cout << "wall : " << startX <<  " " << startY << " " << endX << " " << endY  << endl;
        
    float ballRadius = ball.getRadius();
    float ballX = ball.getX();
    float ballY = ball.getY();
    float ballVY = ball.getVy();
    float ballVX = ball.getVx();
    float ballMass = ball.getMass();


    // Components of the wall vector 
    float WallX1 = wall.getDx();
    float WallY1 = wall.getDy();

    // Components of the vector from ball to the start point of the wall
    float WallX2 = ballX - startX;
    float WallY2 = ballY - startY;

    float EdgeLength = WallX1 * WallX1 + WallY1 * WallY1; // Square of the length of the wall vector



    // dot product of two vectors divided by length of wall vector, normalized between 0 and 1. 
    // Calculates the portion of the wall vector in the shadow of the ball vector ( portion value out of 1)
    float t = max(0.0f, min(EdgeLength, (WallX1 * WallX2 + WallY1 * WallY2))) / EdgeLength;    

    // Coordinates of the closest point of the wall to the ball
    float ClosestPointX = startX + t * WallX1;
	float ClosestPointY = startY + t * WallY1;

    // Distance between ball and closest point of the wall
    float Distance = sqrtf((ballX - ClosestPointX)*(ballX - ClosestPointX) + (ballY - ClosestPointY)*(ballY - ClosestPointY));

    //cout << " distance : "  << fDistance <<  " fedge :  " << fEdgeLength << " fclosest : " << fClosestPointX << " " << fClosestPointY  << " wall :" << fWallX1 << " "<< fWallY1 <<" " << fWallX2 << " " << fWallY2 << " t : " << t  <<endl;



    // If the distance between is equal or smaller than the sum of the radiuses of the wall and ball, collision is occured
    if (Distance <= (ballRadius + wallRadius))
		{   
            // Creating an invisible fake ball at the point of collision moving at opposite velocity
            // to simulate collison. Fake ball mass set to 0.8 times of the ball to simulate energy loss
            // from the collision.


            Ball *fakeball = new Ball(ClosestPointX,ClosestPointY,-ballVX, -ballVY, 0.0f, 0.0f, wallRadius,ballMass * 0.8f);

            // Adding colliding objects to a vector
            vecCollidingObjects.push_back({ &ball, fakeball });

            //Displace current ball away from collision
            float Overlap = 1.0f * (Distance - ballRadius - fakeball->getRadius());
			float ballDX = ballX -( Overlap * (ballX - fakeball->getX()) / Distance );
			float ballDY = ballY - ( Overlap * (ballY - fakeball->getY()) / Distance );
            ball.setPosition(ballDX,ballDY);

            // if collision happens return true
            return true;
        }
    return false;    
			





/*
    float dist = (wall.getEndX() - wall.getStartX()) * (ball.getY() - wall.getStartY()) -
    (ball.getX() - wall.getStartX()) * (wall.getEndY() - wall.getStartY());

    float distanceToWall = abs(dist) / sqrt(pow(wall.getEndX() - wall.getStartX(), 2) + pow(wall.getEndY() - wall.getStartY(), 2));

    float projectedX = wall.getStartX() + (wall.getEndX() - wall.getStartX()) * ((ball.getX() - wall.getStartX()) * (wall.getEndX() - wall.getStartX()) +
    (ball.getY() - wall.getStartY()) * (wall.getEndY() - wall.getStartY())) /
    (pow(wall.getEndX() - wall.getStartX(), 2) + pow(wall.getEndY() - wall.getStartY(), 2));

    float projectedY = wall.getStartY() + (wall.getEndY() - wall.getStartY()) * ((ball.getX() - wall.getStartX()) * (wall.getEndX() - wall.getStartX()) +
    (ball.getY() - wall.getStartY()) * (wall.getEndY() - wall.getStartY())) /
    (pow(wall.getEndX() - wall.getStartX(), 2) + pow(wall.getEndY() - wall.getStartY(), 2));



    if (projectedX < min(startX, endX) - ballRadius ||
    projectedX > max(startX, endX) + ballRadius ||
    projectedY < min(startY, endY) - ballRadius ||
    projectedY > max(startY, endY) + ballRadius) {
        
        return false;
    }

    */
    
        

}

/*
    Resolves the collision between a Wall and a ball

    Time complexity : O(1) Constant Time  (It is not O(n) at this state, because vecCollidingObjects contains only one pair)
    Space complexity : O(1) Constant Space

*/

void Physics::resolveCollision(){
    
    

    float fEfficiency = 1.0f;
	for (auto c : vecCollidingObjects)
	{
		Ball *b1 = c.first, *b2 = c.second;
        float b1X = b1->getX();
        float b1Y = b1->getY();
        float b2X = b2->getX();
        float b2Y = b2->getY();

        float b1Vx = b1->getVx();
        float b1Vy = b1->getVy();
        float b2Vx = b2->getVx();
        float b2Vy = b2->getVy();

        float b1mass = b1->getMass();
        float b2mass = b2->getMass();



		// Distance between balls
		float fDistance = sqrtf((b1X - b2X)*(b1X - b2X) + (b1Y - b2Y)*(b1Y - b2Y));

		// Normal
		float nx = (b2X - b1X) / fDistance;
		float ny = (b2Y - b1Y) / fDistance;

		// Tangent
		float tx = -ny;
		float ty = nx;

		// Dot Product Tangent
		float dpTan1 = b1Vx * tx + b1Vy * ty;
		float dpTan2 = b2Vx * tx + b2Vy * ty;

		// Dot Product Normal
		float dpNorm1 = b1Vx * nx + b1Vy * ny;
		float dpNorm2 = b2Vx * nx + b2Vy * ny;

		// Conservation of momentum in 1D
		float m1 = fEfficiency * (dpNorm1 * (b1mass - b2mass) + 2.0f * b2mass * dpNorm2) / (b1mass + b2mass);
		float m2 = fEfficiency * (dpNorm2 * (b2mass - b1mass) + 2.0f * b1mass * dpNorm1) / (b1mass + b2mass);

        // Calculate the Coulomb's friction forces
        float mu = 0.8f; // Friction coefficient
        float fn1 = b1mass * gravity; // Normal force of ball 1
        float fn2 = b2mass * gravity; // Normal force of ball 2

        // Friction forces
        float ftTan1 = -mu * fn1 * dpTan1;
        float ftTan2 = -mu * fn2 * dpTan2;

        b1->setAcceleration(tx * ftTan1 / b1mass, ty * ftTan1 / b1mass);
        b2->setAcceleration(tx * ftTan2 / b2mass, ty * ftTan2 / b2mass);


		// Update ball velocities
		b1->setVelocity(tx * dpTan1 + nx * m1, ty * dpTan1 + ny * m1 );
		b2->setVelocity(tx * dpTan2 + nx * m2, ty * dpTan2 + ny * m2);
        
		
	}
    vecCollidingObjects.clear();













    /* float ballRadius = ball.getRadius();
    float ballMass = ball.getMass();
    float ballX = ball.getX();
    float ballY = ball.getY();
    float ballVx = ball.getVx();
    float ballVy = ball.getVy();

    float startX = wall.getStartX();
    float startY = wall.getStartY();
    float endX = wall.getEndX();
    float endY = wall.getEndY();
    float normalX = wall.getNormalX();
    float normalY = wall.getNormalY();
    float friction = wall.getFriction();


        

    float dotProduct = ballVx * normalX + ballVy * normalY;
    float fx = -2 * dotProduct * normalX;
    float fy = -2 * dotProduct * normalY;
    float frictionFactor = 1 - friction;

    ball.setVelocity(frictionFactor * (ballVx + fx / ballMass), frictionFactor * (ballVy + fy / ballMass));
        
    float dist = (ballX - startX) * normalY - (ballY - startY) * normalX;
    
    float overlap = ballRadius - abs(dist);
    ball.setPosition(ballX + overlap * normalX, ballY + overlap * normalY);
    
    return ball;
*/

}


