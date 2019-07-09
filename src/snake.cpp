enum Direction { UP, RIGHT, DOWN, LEFT};

class snakeBody {
    
    public:
        snakeBody(unsigned int xPos, unsigned int yPos) {
            this->xPos = xPos;
            this->yPos = yPos;
        }
    
        unsigned int getxPos(){
            return this->xPos;    
        }
    
        unsigned int getyPos(){
            return this->yPos;    
        }
    
        void setxPos(unsigned int newX) {
            this->xPos = newX;
        }
    
        void setyPos(unsigned int newY) {
            this->yPos = newY;
        }
    
        void setPos(unsigned int newX, unsigned int newY) {
            this->xPos = newX;
            this->yPos = newY;
        }
        
        snakeBody * getPrevPart() {
            return this->prevPart;
        }
        
        snakeBody * getNextPart() {
            return this->nextPart;
        }
        
        void setPrevPart(snakeBody * prevPart) {
            this->prevPart = prevPart;
        }
        
        void setNextPart(snakeBody * nextPart) {
            this->nextPart = nextPart;
        }
    
    private:
        unsigned int xPos;
        unsigned int yPos;
        snakeBody * prevPart;
        snakeBody * nextPart;    

};

class snakeHead : public snakeBody {
    
    public:
        snakeHead() : snakeBody(0, 2) {
            length = 3;
            snakeBody * part2 = new snakeBody(0, 1);
            this->setNextPart(part2);
            part2->setPrevPart(this);
            snakeBody * part3 = new snakeBody(0, 0);
            part2->setNextPart(part3);
            part3->setPrevPart(part2);
            this->setTail(part3);
        } 
        
        snakeBody * getTail() {
            return this->tail;
        }
        
        void setTail(snakeBody * tail) {
            this->tail = tail;
        }
        
        void move(Direction dir) {
            snakeBody * current = this->getTail();
            while(current != this) {
                // Move snake body parts forward
                current->setPos(current->getPrevPart()->getxPos(), current->getPrevPart()->getyPos());
                current = current->getPrevPart();    
            }
            switch(dir) {
                // Move snake head to new position
                case UP: this->setyPos((this->getyPos()+1)%8); break;
                case LEFT: this->setxPos((this->getxPos()-1)%8); break;
                case RIGHT: this->setxPos((this->getxPos()+1)%8); break;
                case DOWN: this->setyPos((this->getyPos()-1)%8); break;
            }
        }
        
        void append(snakeBody * newPart) {
            this->getTail()->setNextPart(newPart);
            newPart->setPrevPart(this->getTail());
            this->setTail(newPart);
            length++;    
        }
        
    private:
        unsigned int length;  
        snakeBody * tail;
    
};
