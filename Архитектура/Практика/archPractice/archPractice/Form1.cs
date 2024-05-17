using System.Xml.Serialization;

namespace archPractice
{
    public partial class Form1 : Form, IForm
    {
        private Graphics g;
        public Form1()
        {
            InitializeComponent();
            g = CreateGraphics();
        }
        public void drawCity(int x, int y)
        {
            g.FillEllipse(Brushes.Red, x - 5, y - 5, 10, 10);
        }
        public void drawCityConnection(Point city1, Point city2)
        {
            g.DrawLine(Pens.Black, city1, city2);
        }
        public void addMouseListener(MouseEventHandler handler)
        {
            this.MouseClick += handler;
        }
        public void addClearButtonListener(EventHandler handler)
        {
            this.clearButton.Click += handler;
        }
        public void addSolveButtonListener(EventHandler handler)
        {
            this.solveButton.Click += handler;
        }
        public void addMatrixColumn(string name)
        {
            dataMatrix.Columns.Add(name, name);
            int matrixSize = dataMatrix.Rows.Count;
            dataMatrix.Rows.Add();
            dataMatrix.Rows[matrixSize].HeaderCell.Value = name;
            dataMatrix.Rows[matrixSize].Cells[matrixSize].Value = "0";
            dataMatrix.Rows[matrixSize].Cells[matrixSize].ReadOnly = true;
            dataMatrix.Columns[matrixSize].Width = 60;
        }
        public int[,] getDataMatrix()
        {
            int[,] matrix = new int[dataMatrix.Rows.Count, dataMatrix.Rows[0].Cells.Count];
            for (int x = 0; x < dataMatrix.Columns.Count; x++)
            {
                for (int y = 0; y < dataMatrix.Rows.Count; y++)
                {

                    if (dataMatrix.Rows[y].Cells[x].Value != null)
                    {
                        string stringValue = dataMatrix.Rows[y].Cells[x].Value.ToString();
                        if (Int32.TryParse(stringValue, out int value))
                        {
                            matrix[x, y] = value;
                        }
                    }
                }
            }
            return matrix;
        }

        private void dataMatrix_CellValueChanged(object sender, DataGridViewCellEventArgs e)
        {
            if (e.ColumnIndex == -1) { return; }
            if (dataMatrix.Rows[e.RowIndex].Cells[e.ColumnIndex] == null) { return; }
            string newValue = dataMatrix.Rows[e.RowIndex].Cells[e.ColumnIndex].Value.ToString();
            dataMatrix.Rows[e.ColumnIndex].Cells[e.RowIndex].Value = newValue;
        }

        public void clear()
        {
            g.Clear(Control.DefaultBackColor);
            dataMatrix.Rows.Clear();
            dataMatrix.Columns.Clear();
        }
    }
}