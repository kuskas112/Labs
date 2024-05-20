using System.Xml.Serialization;

namespace archPractice
{
    public partial class Form1 : Form, IForm
    {
        private Graphics g;
        private int cityCount = 1;
        public Form1()
        {
            InitializeComponent();
            errorLabel.Text = "";
            solutionLabel.Text = "";
            g = CreateGraphics();
        }
        public void showError(string err)
        {
            errorLabel.Text = err;
        }
        public void showSolution(string sol)
        {
            errorLabel.Text = "";
            solutionLabel.Text = sol;
        }
        public void drawCity(int x, int y)
        {
            g.FillEllipse(Brushes.Red, x - 5, y - 5, 10, 10);
            g.DrawString(cityCount.ToString(), new Font("Arial", 10), Brushes.Black, new Point(x - 25, y - 20));
            cityCount++;
        }
        public void drawCityConnection(Point city1, Point city2)
        {
            g.DrawLine(Pens.Black, city1, city2);
        }
        public void drawSolutionCityConnection(Point city1, Point city2)
        {
            g.DrawLine(Pens.Blue, city1, city2);
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
        public int[,] getDataMatrix(out bool boolResult)
        {
            int size = dataMatrix.Rows.Count;
            if(size <= 0)
            {
                boolResult = false;
                return new int[,] {};
            }
            int[,] matrix = new int[size, size];
            for (int x = 0; x < size; x++)
            {
                for (int y = 0; y < size; y++)
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
            boolResult = true;
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
            errorLabel.Text = "";
            solutionLabel.Text = "";
            cityCount = 1;
        }

    }
}