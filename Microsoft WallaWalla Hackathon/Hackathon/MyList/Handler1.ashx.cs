using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Web;
using MyList.Controllers;
using MyList.Models;
using System.Drawing;

namespace MyList
{
    /// <summary>
    /// Summary description for Handler1
    /// </summary>
    public class Handler1 : IHttpHandler
    {
        private MyListDBEntities db = new MyListDBEntities();

        public void ProcessRequest(HttpContext context)
        {
            byte[] img;

            HttpRequest r = context.Request;
            string listingId = r.QueryString["listingId"];
            if (listingId != null && listingId != "undefined")
            {
                int id = int.Parse(listingId);

                Posting updatedPosting = db.Postings.Find(id);

                context.Response.ContentType = "text/plain";
                if (updatedPosting == null)
                {
                    context.Response.Write("Posting " + id + " doesn't exists");
                }

                HttpFileCollection files = r.Files;

                for (int i = 0; i < files.Count; i++)
                {
                    HttpPostedFile file = files[i];
                    if (file.ContentLength > 0)
                    {
                        img = new byte[file.ContentLength];
                        file.InputStream.Read(img, 0, file.ContentLength);
                        if (i == 0)
                            updatedPosting.image1 = img;
                        else if (i == 1)
                            updatedPosting.image2 = img;
                        else if (i == 2)
                            updatedPosting.image3 = img;
                        else if (i == 3)
                            updatedPosting.image4 = img;
                    }
                }

                int filesUploaded = files.Count;
                if (filesUploaded > 4)
                {
                    //context.Response.Write("Successfully uploaded 4 files to the server");
                }
                else
                {
                    //context.Response.Write("Successfully uploaded " + filesUploaded + " files to the server");
                }

                updatedPosting.images = filesUploaded;

                PostingsController MyPostingController = new PostingsController();
                MyPostingController.PutPosting(id, updatedPosting);
            }
            else
            {
                r = context.Request;
                string customerId = r.QueryString["customerId"];
                if (customerId != null && customerId != "undefined")
                {
                    int id = int.Parse(customerId);

                    Customer updatedCustomer = db.Customers.Find(id);

                    if (updatedCustomer == null)
                    {
                        context.Response.ContentType = "text/plain";
                        context.Response.Write("Posting " + id + " doesn't exists");
                    }

                    HttpFileCollection files = r.Files;

                    for (int i = 0; i < files.Count; i++)
                    {
                        HttpPostedFile file = files[i];
                        if (file.ContentLength > 0)
                        {
                            img = new byte[file.ContentLength];
                            file.InputStream.Read(img, 0, file.ContentLength);
                            updatedCustomer.image = img;
                        }
                    }

                    CustomersController MyCustomerController = new CustomersController();
                    MyCustomerController.PutCustomer(id, updatedCustomer);
                }
                else {
                    context.Response.ContentType = "text/plain";
                    context.Response.Write("Wrong usage of GetImageFile webservice.  Please provide postingId or customerId values.");
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