using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SixtyFourFive
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                string filename = openFileDialog1.FileName;
                if(filename.EndsWith(".txt"))
                {
                    this.ConvertToBinary(filename);
                }
                else
                {
                    this.ConvertToText(filename);
                }
            }
            MessageBox.Show("Done");
        }



        private void ConvertToText(string filename)
        {
            if (!File.Exists(filename))
                throw new ApplicationException("File not found: " + filename);

            string extention = Path.GetExtension(filename);
            string outputname = filename.Replace(extention, ".txt");

            using(var input = new FileStream(filename, FileMode.Open))
            {
                int length = (int)input.Length;
                var data = new byte[length];
                input.Read(data, 0, length);
                string text = Convert.ToBase64String(data);

                using (var output = new StreamWriter(outputname))
                {
                    output.Write(text);
                }
            }
        }

        private void ConvertToBinary(string filename)
        {
            if (!File.Exists(filename))
                throw new ApplicationException("File not found: " + filename);

            string extention = Path.GetExtension(filename);
            string outputname = filename.Replace(extention, ".dat");

            using (var input = new StreamReader(filename))
            {
                string text = input.ReadToEnd();
                var data = Convert.FromBase64String(text);

                using (var output = new BinaryWriter(File.Open(outputname, FileMode.Create)))
                {
                    output.Write(data);
                }
            }


        }

        private void e7xitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }
    }
}
