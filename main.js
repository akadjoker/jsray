class Bunny
{
    constructor()
    {
        this.x = core.random(0, 840);
        this.y = core.random(0, 450);
        this.speedX = core.random(-256,256)/60.0
        this.speedY = core.random(-256,256)/60.0
    }

    update()
    {
        this.x += this.speedX
        this.y += this.speedY

        if (this.x < 0 || this.x > 840)
        {
            this.speedX = -this.speedX
        }
        if (this.y < 0 || this.y > 450)
        {
            this.speedY = -this.speedY
        }
        graphics.draw(1, this.x, this.y);
    }
}

window.init(840, 450, "Raylib with QuickJS")

assets.loadTexture(1, "wabbit_alpha.png")

let bunnies =[]

while (!window.shouldClose()) 
{


    if (mouse.down(0))
    {
        
         for (let i = 0; i < 100; i++)
        {
            bunnies.push(new Bunny())
        }
    }

  
    graphics.clear(0, 0, 45);
    graphics.begin()

    graphics.setColor(255, 255, 255)

    for (let i = 0; i < bunnies.length; i++)
        {
            bunnies[i].update()
        }
    
    
        graphics.setColor(0,0,0)
        graphics.rectangle(5,5,150,60,false)
        
    graphics.setColor(255, 0, 0)
    graphics.showFPS(10, 10)
    graphics.setTextSize(20)
    graphics.text(10,40,"Bunnies"+bunnies.length)
    graphics.setColor(255, 255, 255)
    
    graphics.draw(1, 100, 100);




    graphics.end()



}


window.close();