using System.Collections;
using System.Collections.Generic;

namespace Snake
{
    internal class Snake : IEnumerable
    {
        //private Point _head;
        //private Point _tail;

        private Direction _direction;

        // Index [0] - head, index [Count - 1] - tail
        private List<Point> _path;

        private bool isJustAte = false;

        internal Point Tail
        {
            get { return _path[_path.Count - 1]; }
        }

        internal Point Head
        {
            get { return _path[0]; }
            set { _path[0] = value; }
        }

        internal Direction CurrentDirection
        {
            get { return _direction; }
        }

        internal Snake(Point head, Point tail)
        {
            //_head = head;
            //_tail = tail;

            _path = new List<Point>();
            _path.Add(head);
            _path.Add(tail);
        }

        internal Snake(int headX, int headY, int tailX, int tailY)
        {
            Point head = new Point(headX, headY);
            Point tail = new Point(tailX, tailY);

            _path = new List<Point>();
            _path.Add(head);
            _path.Add(tail);
        }

        internal void Move(Direction direction)
        {
            _direction = direction;
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return _path.GetEnumerator();
        }

        internal void DoStep()
        {
            if (isJustAte)
            {
                isJustAte = false;
                return;
            }

            Point headPoint = _path[0];
            
            int x = headPoint.X;
            int y = headPoint.Y;
            
            switch (_direction)
            {
                case Direction.Up:
                    y -= 1;
                    break;
                case Direction.Right:
                    x += 1;
                    break;
                case Direction.Down:
                    y += 1;
                    break;
                case Direction.Left:
                    x -= 1;
                    break;
            }

            Point newHeadPoint = new Point(x, y);

            // Clear tail cell
            _path.RemoveAt(_path.Count - 1);
            // Set new head cell
            _path.Insert(0, newHeadPoint);
        }

        public void Eat(Point foodPoint)
        {
            _path.Insert(_path.Count - 1, _path[_path.Count - 1]);

            // WARNING: No more needed. Can be deleted from all instances.
            //isJustAte = true;
        }

        internal Rect GetBounds()
        {
            Point point = _path[0];
            int top = point.Y, right = point.X, down = point.Y, left = point.X;

            for (int i = 1; i < _path.Count; i++)
            {
                point = _path[i];

                if (point.Y < top)
                    top = point.Y;

                if (point.X > right)
                    right = point.X;

                if (point.Y > down)
                    down = point.Y;

                if (point.X < left)
                    left = point.X;
            }

            return new Rect(left, top, right - left + 1, down - top + 1);
        }
    }
}
