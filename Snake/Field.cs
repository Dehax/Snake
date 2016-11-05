
namespace Snake
{
    internal class Field
    {
        internal enum CellType
        {
            Empty = 0,
            Snake = 1,
            Food = 2
        }

        // Size
        private int _fieldWidth;
        private int _fieldHeight;

        // Data
        private CellType[,] _field;

        internal CellType[,] Cell
        {
            get { return _field; }
        }

        internal Field(int fieldWidth, int fieldHeight)
        {
            _fieldWidth = fieldWidth;
            _fieldHeight = fieldHeight;

            _field = new CellType[_fieldWidth, _fieldHeight];

            ResetField();
        }

        internal void ResetField()
        {
            for (int i = 0; i < _fieldWidth; i++)
            {
                for (int j = 0; j < _fieldHeight; j++)
                {
                    _field[i, j] = CellType.Empty;
                }
            }
        }

        internal CellType GetCell(int x, int y)
        {
            return _field[x, y];
        }
    }
}
