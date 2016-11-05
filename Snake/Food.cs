using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Snake
{
    internal class Food
    {
        internal Point Position;
        
        internal Food(int x, int y)
        {
            Position = new Point(x, y);
        }
    }
}
