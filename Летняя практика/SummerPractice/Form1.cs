using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Linq.Expressions;
using System.Diagnostics;
using System.Xml.Schema;

namespace SummerPractice
{
    public partial class Form1 : Form
    {
        Graphics g;
        Point center;
        int scale = 20;
        double gap = 0.5;
        double xFrom = 0;
        double xTo = 0;
        public Form1()
        {
            InitializeComponent();
        }

        public void drawXLine()
        {
            Pen pen; 
            int count = (center.X) / scale;
            for (int i = 0; i < count; i++)
            {
                if (i % 2 == 0)
                {
                    pen = Pens.Black;
                }
                else
                {
                    pen = Pens.Red;
                }

                g.DrawLine(pen, center.X + scale * i, center.Y, center.X + scale * (i+1), center.Y);
                g.DrawLine(pen, center.X + scale * -i, center.Y, center.X + scale * (-i-1), center.Y);

                if (i != 0)
                {
                    g.DrawLine(Pens.LightGray, center.X + scale * i, 0, center.X + scale * i, this.Height);
                    g.DrawLine(Pens.LightGray, center.X + scale * -i, 0, center.X + scale * -i, this.Height);
                }
            }
        }

        public void drawYLine()
        {
            Pen pen;
            int count = (center.Y) / scale;
            for (int i = 0; i < count; i++)
            {
                if (i % 2 == 0)
                {
                    pen = Pens.Black;
                }
                else
                {
                    pen = Pens.Red;
                }

                g.DrawLine(pen, center.X, center.Y + scale * i, center.X, center.Y + scale * (i+1));
                g.DrawLine(pen, center.X, center.Y + scale * -i, center.X, center.Y + scale * (-i-1));

                if (i != 0)
                {
                    g.DrawLine(Pens.LightGray, 0, center.Y + scale * i, this.Width, center.Y + scale * i);
                    g.DrawLine(Pens.LightGray, 0, center.Y + scale * -i, this.Width, center.Y + scale * -i);
                }
            }
        }

        private List<Point> calculateFunction()
        {
            List<Point> points = new List<Point>();
            string func = input.Text;
            try
            {
                for (double x = xFrom; x <= xTo; x += gap)
                {
                    double result = calculatePoint(func, x);
                    points.Add(new Point(center.X + (int)(x * scale), center.Y - (int)(result * scale)));
                }
            }
            catch (Exception e)
            {
                errorLabel.Text = e.Message;
                return points;
            }
            return points;
        }

        private double calculatePoint(string func, double x)
        {
            string xValue = String.Format("{0:F10}", x);
            string expr = func.Replace("x", xValue);
            expr = expr.Replace(",", ".");
            double res = 0;
            res = StringToFormula.Eval(expr);          
            return res;
        }

        private void showResult()
        {
            List<Point> points = calculateFunction();

            for (int i = 0; i < points.Count; i++)
            {
                if(checkPointInBounds(points[i]) == false)
                {
                    continue;
                }
                drawPoint(points[i], Brushes.Red);

                if (i > 0)
                {
                    if (checkPointInBounds(points[i-1]) == false)
                    {
                        continue;
                    }
                    g.DrawLine(Pens.Aqua, points[i - 1], points[i]);
                }
            }
        }

        private bool checkPointInBounds(Point point)
        {
            if (Math.Abs(this.Width - point.X) > this.Width*2 || Math.Abs(this.Height - point.Y) > this.Height*2)
            {
                return false;
            }
            return true;
        }

        private void drawPoint(Point point, Brush brush, int size = 4)
        {
            g.FillEllipse(brush, point.X-size/2, point.Y-size/2, size, size);
        }

        private bool parseInput()
        {
            if (!Int32.TryParse(scaleTextBox.Text, out scale))
            {
                return false;
            }
            if (!double.TryParse(gapTextBox.Text, out gap))
            {
                return false;
            }
            if (!double.TryParse(xFromTextBox.Text, out xFrom))
            {
                return false;
            }
            if (!double.TryParse(xToTextBox.Text, out xTo))
            {
                return false;
            }

            return true;
        }

        private void paintButton_Click(object sender, EventArgs e)
        {
            g = CreateGraphics();
            g.Clear(DefaultBackColor);
            center = new Point(this.Width / 2, this.Height / 2);
            errorLabel.Text = "";
            if (parseInput())
            {
                drawXLine();
                drawYLine();
                showResult();
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            paintButton_Click(sender, e);
            double x, y;
            if (!double.TryParse(xValueTextBox.Text, out x))
            {
                return;
            }
            y = calculatePoint(input.Text, x);
            yFromTextBox.Text = y.ToString();
            Point foundPoint = new Point(center.X + (int)(x * scale), center.Y - (int)(y * scale));
            this.drawPoint(foundPoint, Brushes.Blue, 10);
        }
    }
}
