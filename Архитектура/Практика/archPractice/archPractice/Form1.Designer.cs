namespace archPractice
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            DataPanel = new Panel();
            dataMatrix = new DataGridView();
            clearButton = new Button();
            greetingLabel = new Label();
            solveButton = new Button();
            DataPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)dataMatrix).BeginInit();
            SuspendLayout();
            // 
            // DataPanel
            // 
            DataPanel.BackColor = SystemColors.ControlDark;
            DataPanel.Controls.Add(solveButton);
            DataPanel.Controls.Add(dataMatrix);
            DataPanel.Controls.Add(clearButton);
            DataPanel.Controls.Add(greetingLabel);
            DataPanel.Dock = DockStyle.Right;
            DataPanel.Location = new Point(517, 0);
            DataPanel.Name = "DataPanel";
            DataPanel.Size = new Size(416, 450);
            DataPanel.TabIndex = 0;
            // 
            // dataMatrix
            // 
            dataMatrix.AllowUserToAddRows = false;
            dataMatrix.AllowUserToDeleteRows = false;
            dataMatrix.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dataMatrix.Location = new Point(27, 94);
            dataMatrix.Name = "dataMatrix";
            dataMatrix.RowHeadersWidth = 62;
            dataMatrix.RowTemplate.Height = 33;
            dataMatrix.Size = new Size(360, 225);
            dataMatrix.TabIndex = 2;
            dataMatrix.CellValueChanged += dataMatrix_CellValueChanged;
            // 
            // clearButton
            // 
            clearButton.Dock = DockStyle.Bottom;
            clearButton.Location = new Point(0, 416);
            clearButton.Name = "clearButton";
            clearButton.Size = new Size(416, 34);
            clearButton.TabIndex = 1;
            clearButton.Text = "Очистить";
            clearButton.UseVisualStyleBackColor = true;
            // 
            // greetingLabel
            // 
            greetingLabel.AutoSize = true;
            greetingLabel.Location = new Point(133, 31);
            greetingLabel.Name = "greetingLabel";
            greetingLabel.Size = new Size(169, 25);
            greetingLabel.TabIndex = 0;
            greetingLabel.Text = "Best TSP solver ever";
            // 
            // solveButton
            // 
            solveButton.Dock = DockStyle.Bottom;
            solveButton.Location = new Point(0, 382);
            solveButton.Name = "solveButton";
            solveButton.Size = new Size(416, 34);
            solveButton.TabIndex = 3;
            solveButton.Text = "Решить";
            solveButton.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(10F, 25F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(933, 450);
            Controls.Add(DataPanel);
            FormBorderStyle = FormBorderStyle.Fixed3D;
            Name = "Form1";
            Text = "Form1";
            DataPanel.ResumeLayout(false);
            DataPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)dataMatrix).EndInit();
            ResumeLayout(false);
        }

        #endregion

        private Panel DataPanel;
        private Label greetingLabel;
        private Button clearButton;
        public DataGridView dataMatrix;
        private Button solveButton;
    }
}