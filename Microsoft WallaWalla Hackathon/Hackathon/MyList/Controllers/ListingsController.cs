using MyList.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web.Http;
using System.Data.Entity;
using System.Data.Entity.Infrastructure;
using System.Data.Entity.Core.Objects;

namespace MyList.Controllers
{
    public class ListingsController : ApiController
    {

        Listing[] listings = new Listing[] 
        { 
            new Listing { Id = 1, Name = "Tomato Soup", Category = "Groceries", Price = 1 }, 
            new Listing { Id = 2, Name = "Yo-yo", Category = "Toys", Price = 3.75M }, 
            new Listing { Id = 3, Name = "Hammer", Category = "Hardware", Price = 16.99M } 
        };

        public ObjectResult<int?> GetValidateLogin(string email, string passwd)
        {
            ObjectResult<int?> result = db.LoginValidation(email, passwd);
             
            return result;
        }

        public IEnumerable<Listing> GetAllListings()
        {
            return listings;
        }

        public IHttpActionResult GetListing(int id)
        {
            var listing = listings.FirstOrDefault((p) => p.Id == id);
            if (listing == null)
            {
                return NotFound();
            }
            return Ok(listing);
        }

        private MyListDBEntities db = new MyListDBEntities();

        public IEnumerable<MyListings_Result> GetListingsForCustomer(int customerId)
        {
            ObjectResult<MyListings_Result> listings = db.MyListings(customerId);

            return listings;
        }

        public ObjectResult<IndividualListing_Result> GetIndividualListing(int listingId)
        {
            ObjectResult<IndividualListing_Result> listing = db.IndividualListing(listingId);

            return listing;
        }

        public ObjectResult<ListingCategorySearch_Result> GetCategoryListings(string category) 
        {
            ObjectResult<ListingCategorySearch_Result> listings = db.ListingCategorySearch(category);

            return listings;
        }
        public ObjectResult<ListingTitleSearch_Result> GetTitleKeywordListings(string param1)
        {
            ObjectResult<ListingTitleSearch_Result> listings = db.ListingTitleSearch(param1);
            if (listings == null)
                Console.WriteLine("Empty Result");

            return listings;
        }

        public ObjectResult<ListingOther1Search_Result> GetOther1KeywordListings(string keyword)
        {
            ObjectResult<ListingOther1Search_Result> listings = db.ListingOther1Search(keyword);
            if (listings == null)
                Console.WriteLine("Empty Result");

            return listings;
        }
    }
}
