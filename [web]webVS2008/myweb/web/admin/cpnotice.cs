namespace web.admin
{
    using FredCK.FCKeditorV2;
    using System;
    using System.Web.UI;
    using System.Web.UI.WebControls;
    using web;

    public class cpnotice : Page
    {
        protected Button btnedit;
        protected FCKeditor edit;

        private void btnedit_Click(object sender, EventArgs e)
        {
            if (this.edit.Value.ToString() == "")
            {
                base.Response.Write("<script language=javascript>alert(\"公告內容不能為空\")</script>");
            }
            else
            {
                if (new DataProviders().ExecScalarOne("select count(*) from web_notice") == "0")
                {
                    new DataProviders().ExecuteSql("insert into web_notice (notice) values ('" + new system().ChkSql(this.edit.Value.ToString()) + "')");
                }
                else
                {
                    new DataProviders().ExecuteSql("update web_notice set notice='" + new system().ChkSql(this.edit.Value.ToString()) + "'");
                }
                new system().loadConfig(1);
            }
        }

        private void InitializeComponent()
        {
            this.btnedit.Click += new EventHandler(this.btnedit_Click);
            base.Load += new EventHandler(this.Page_Load);
        }

        protected override void OnInit(EventArgs e)
        {
            this.InitializeComponent();
            base.OnInit(e);
        }

        private void Page_Load(object sender, EventArgs e)
        {
            new system().loadConfig(0);
            new WebLogic().isadmin();
            if (!this.Page.IsPostBack)
            {
                this.edit.Value = new DataProviders().ExecScalarOne("select notice from web_notice");
            }
        }
    }
}
