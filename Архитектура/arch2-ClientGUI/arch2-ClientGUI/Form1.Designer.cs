namespace arch2_ClientGUI
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
            this.panel1 = new System.Windows.Forms.Panel();
            this.connectButton = new System.Windows.Forms.Button();
            this.portLabel = new System.Windows.Forms.Label();
            this.portText = new System.Windows.Forms.TextBox();
            this.ipLabel = new System.Windows.Forms.Label();
            this.ipText = new System.Windows.Forms.TextBox();
            this.chatText = new System.Windows.Forms.TextBox();
            this.peopleList = new System.Windows.Forms.ListBox();
            this.textToSend = new System.Windows.Forms.TextBox();
            this.sendButton = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.LightGray;
            this.panel1.Controls.Add(this.connectButton);
            this.panel1.Controls.Add(this.portLabel);
            this.panel1.Controls.Add(this.portText);
            this.panel1.Controls.Add(this.ipLabel);
            this.panel1.Controls.Add(this.ipText);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Top;
            this.panel1.Location = new System.Drawing.Point(0, 0);
            this.panel1.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(496, 137);
            this.panel1.TabIndex = 0;
            // 
            // connectButton
            // 
            this.connectButton.Location = new System.Drawing.Point(209, 68);
            this.connectButton.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.connectButton.Name = "connectButton";
            this.connectButton.Size = new System.Drawing.Size(107, 38);
            this.connectButton.TabIndex = 5;
            this.connectButton.Text = "Connect";
            this.connectButton.UseVisualStyleBackColor = true;
            this.connectButton.Click += new System.EventHandler(this.connectButton_Click);
            // 
            // portLabel
            // 
            this.portLabel.AutoSize = true;
            this.portLabel.Location = new System.Drawing.Point(309, 25);
            this.portLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.portLabel.Name = "portLabel";
            this.portLabel.Size = new System.Drawing.Size(44, 25);
            this.portLabel.TabIndex = 4;
            this.portLabel.Text = "Port";
            // 
            // portText
            // 
            this.portText.Location = new System.Drawing.Point(359, 20);
            this.portText.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.portText.Name = "portText";
            this.portText.Size = new System.Drawing.Size(81, 31);
            this.portText.TabIndex = 3;
            this.portText.Text = "8888";
            // 
            // ipLabel
            // 
            this.ipLabel.AutoSize = true;
            this.ipLabel.Location = new System.Drawing.Point(41, 25);
            this.ipLabel.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.ipLabel.Name = "ipLabel";
            this.ipLabel.Size = new System.Drawing.Size(27, 25);
            this.ipLabel.TabIndex = 2;
            this.ipLabel.Text = "IP";
            // 
            // ipText
            // 
            this.ipText.Location = new System.Drawing.Point(74, 20);
            this.ipText.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.ipText.Name = "ipText";
            this.ipText.Size = new System.Drawing.Size(187, 31);
            this.ipText.TabIndex = 1;
            this.ipText.Text = "127.0.0.1";
            // 
            // chatText
            // 
            this.chatText.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.chatText.Location = new System.Drawing.Point(0, 147);
            this.chatText.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.chatText.Multiline = true;
            this.chatText.Name = "chatText";
            this.chatText.ReadOnly = true;
            this.chatText.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.chatText.Size = new System.Drawing.Size(348, 417);
            this.chatText.TabIndex = 1;
            // 
            // peopleList
            // 
            this.peopleList.FormattingEnabled = true;
            this.peopleList.ItemHeight = 25;
            this.peopleList.Location = new System.Drawing.Point(359, 162);
            this.peopleList.Margin = new System.Windows.Forms.Padding(4, 5, 4, 5);
            this.peopleList.Name = "peopleList";
            this.peopleList.Size = new System.Drawing.Size(118, 404);
            this.peopleList.TabIndex = 2;
            // 
            // textToSend
            // 
            this.textToSend.Location = new System.Drawing.Point(12, 572);
            this.textToSend.Name = "textToSend";
            this.textToSend.Size = new System.Drawing.Size(336, 31);
            this.textToSend.TabIndex = 3;
            // 
            // sendButton
            // 
            this.sendButton.Location = new System.Drawing.Point(359, 572);
            this.sendButton.Name = "sendButton";
            this.sendButton.Size = new System.Drawing.Size(118, 31);
            this.sendButton.TabIndex = 4;
            this.sendButton.Text = "Send";
            this.sendButton.UseVisualStyleBackColor = true;
            this.sendButton.Click += new System.EventHandler(this.sendButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(496, 615);
            this.Controls.Add(this.sendButton);
            this.Controls.Add(this.textToSend);
            this.Controls.Add(this.peopleList);
            this.Controls.Add(this.chatText);
            this.Controls.Add(this.panel1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Panel panel1;
        private Label ipLabel;
        private TextBox ipText;
        private Label portLabel;
        private TextBox portText;
        private Button connectButton;
        private TextBox chatText;
        private ListBox peopleList;
        private TextBox textToSend;
        private Button sendButton;
    }
}