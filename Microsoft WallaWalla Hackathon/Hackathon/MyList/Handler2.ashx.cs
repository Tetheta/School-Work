using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Net;
using System.IO;
using MyList.Controllers;
using MyList.Models;

namespace MyList
{
    /// <summary>
    /// Summary description for Handler2
    /// </summary>
    public class Handler2 : IHttpHandler
    {
        private PostingsController MyPostingController = new PostingsController();
        private MyListDBEntities db = new MyListDBEntities();

        public void ProcessRequest(HttpContext ctx)
        {
            string listingId = ctx.Request.QueryString["listingId"];
            if (listingId != null) {
                int id = int.Parse(listingId);
                string imageNumber = ctx.Request.QueryString["imageNumber"];

                Posting posting = db.Postings.Find(id);

                if (posting == null)
                {
                    ctx.Response.ContentType = "text/plain";
                    ctx.Response.Write("Posting " + id + " doesn't exists");
                }
                else
                {
                    byte[] image = null;
                    if (imageNumber == "1")
                    {
                        image = posting.image1;
                    }
                    else if (imageNumber == "2")
                    {
                        image = posting.image2;
                    }
                    else if (imageNumber == "3")
                    {
                        image = posting.image3;
                    }
                    else if (imageNumber == "4")
                    {
                        image = posting.image4;
                    }
                    if (image != null) { 
                        ctx.Response.ContentType = "application/octet-stream";
                        ctx.Response.BinaryWrite(image);
                    }
                }
            }
            else
            {
                string customerId = ctx.Request.QueryString["customerId"];
                if (customerId != null)
                {
                    int id = int.Parse(customerId);
                    Customer customer  = db.Customers.Find(id);

                    if (customer == null)
                    {
                        ctx.Response.ContentType = "text/plain";
                        ctx.Response.Write("Customer " + id + " doesn't exists");
                    }
                    else { 
                        byte[] image = null;
                        image = customer.image;

                        if (image != null)
                        {
                            ctx.Response.ContentType = "application/octet-stream";
                            ctx.Response.BinaryWrite(image);
                        }
                    }
                }
                else
                {
                    ctx.Response.ContentType = "text/plain";
                    ctx.Response.Write("Wrong usage of UploadImageFile webservice.  Please provide postingId or customerId values.");
                }
            }

        }

        public bool IsReusable
        {
            get
            {
                return false;
            }
        }
    }
}